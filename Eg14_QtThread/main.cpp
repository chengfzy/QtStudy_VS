#include "Eg14_QtThread.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg14_QtThread w;
	w.show();
	return a.exec();
}
