#include "Eg07_ImageListWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg07_ImageListWidget w;
	w.show();
	return a.exec();
}
