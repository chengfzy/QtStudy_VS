#include "Eg12_FramePreview.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Eg12_FramePreview w;
	w.show();
	return a.exec();
}
