#include "pictureedit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PictureEdit w;
	w.show();
	return a.exec();
}
