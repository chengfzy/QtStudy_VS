#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QPushButton* pButton = new QPushButton("TestButon", this);
	pButton->setFixedSize(1000, 100);

	QScrollArea* pScrollArea = new QScrollArea(this);
	pScrollArea->setWidget(pButton);

	this->setCentralWidget(pScrollArea);

}
