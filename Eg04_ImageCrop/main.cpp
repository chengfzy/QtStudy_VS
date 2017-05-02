#include "Eg04_ImageCrop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg04_ImageCrop w;
	w.show();
	return a.exec();
}
