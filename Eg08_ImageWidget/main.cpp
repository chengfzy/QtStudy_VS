#include "Eg08_ImageWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg08_ImageWidget w;
	w.show();
	return a.exec();
}
