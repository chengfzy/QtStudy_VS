#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QTime>
#include "GraphWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

	GraphWidget* widget = new GraphWidget;

	QMainWindow mainWindow;
	mainWindow.setCentralWidget(widget);

	mainWindow.show();
	return a.exec();
}
