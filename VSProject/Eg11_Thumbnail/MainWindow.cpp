#include "MainWindow.h"
#include "ThumbnailThread.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	waitseconds = 1;

	setFixedSize(600, 400);
	setWindowTitle("Thumbnail Thread");
	previewwidget = new QWidget(this);
	previewwidget->setFixedSize(600, 350);
	previewwidget->setAutoFillBackground(true);

	QPushButton* pButton = new QPushButton("Open pictures..", this);
	pButton->setGeometry(450, 360, 130, 35);
	connect(pButton, &QPushButton::clicked, this, &MainWindow::openFiles);

	QGridLayout* layout = new QGridLayout(previewwidget);
}


void MainWindow::openFiles()
{
	waitseconds = 1;//reset

	QStringList list = QFileDialog::getOpenFileNames(this, "Open one or more pictures", "", "*.jpg *.png *.bmp");
	if (list.count() == 0)
	{
		return;
	}

	//open files one by one, and create thread to create thumbnail for each file
	QStringList::Iterator it = list.begin();
	while (it != list.end())
	{
		createThumbnail(*it);
		++it;
	}
}

void MainWindow::createThumbnail(const QString& filename)
{
	qDebug() << filename;
	ThumbnailThread* thread = new ThumbnailThread(filename, 10 - waitseconds);
	waitseconds++;
	connect(thread, &ThumbnailThread::thumbnailFinished, this, &MainWindow::addThumbnail);
	connect(thread, &ThumbnailThread::thumbnailFailed, this, &MainWindow::showError);
	connect(thread, &ThumbnailThread::thumbnailFinished, this, &MainWindow::deleteThread);
	thread->start();
}

void MainWindow::deleteThread()
{
	QObject* obj = sender();
	ThumbnailThread * th = qobject_cast<ThumbnailThread*>(obj);
	qDebug() << "delete thread..." << th->waitseconds();
	obj->deleteLater();
}

void MainWindow::addThumbnail(QImage smallpm)
{
	static int i = 0;
	static int j = 0;

	qWarning() << "thumbnail create successfully (" << i << ", " << j << ")";
	qWarning() << "Small PM:" << smallpm << smallpm.size();
	QLabel* label = new QLabel;
	label->setPixmap(QPixmap::fromImage(smallpm));
	QGridLayout* gl = qobject_cast<QGridLayout*>(previewwidget->layout());
	gl->addWidget(label, j, i);
	label->show();
	qWarning() << "Label:" << label << label->isVisible();
	i++;
	if (i > previewwidget->width() / smallpm.width())
	{
		i = 0;
		j++;
	}
}

void MainWindow::showError(const QString filename)
{
	QMessageBox::information(this, "Error!", filename + " is not a valid picture file.");
}
