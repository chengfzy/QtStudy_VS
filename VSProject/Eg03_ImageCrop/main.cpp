#include "Eg03_ImageCrop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg03_ImageCrop w;
	w.show();
	return a.exec();
}
