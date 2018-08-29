#include "Eg06_RangeSlider.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg06_RangeSlider w;
	w.show();
	return a.exec();
}
