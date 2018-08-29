#include "Eg14_ProgressDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg14_ProgressDialog w;
	w.show();
	return a.exec();
}
