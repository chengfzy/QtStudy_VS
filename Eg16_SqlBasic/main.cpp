#include "Eg16_SqlBasic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg16_SqlBasic w;
	w.show();
	return a.exec();
}
