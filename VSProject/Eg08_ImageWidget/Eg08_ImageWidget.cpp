#include "Eg08_ImageWidget.h"

Eg08_ImageWidget::Eg08_ImageWidget(QWidget *parent)
	: QMainWindow(parent)
{
	//image viewer
	ImageViewer* leftImageViewer = new ImageViewer();
	leftImageViewer->SetImage(QPixmap(tr(":/img/spring")));
	
	ImageViewer* rightImageViewer = new ImageViewer();
	rightImageViewer->SetImage(QPixmap(tr(":/img/orange")));


	QSplitter* splitter = new QSplitter();
	splitter->addWidget(leftImageViewer);
	splitter->addWidget(rightImageViewer);	


	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(splitter);
	layout->addWidget(new QLabel("Image Show"));

	QWidget* mainWidget = new QWidget(this);
	mainWidget->setLayout(layout);


	setCentralWidget(mainWidget);
}
