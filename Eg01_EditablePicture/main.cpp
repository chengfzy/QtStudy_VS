#include "Eg01_EditablePicture.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg01_EditablePicture w;
	w.show();
	return a.exec();
}
