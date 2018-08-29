#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "TimeLineWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

#if 1
	TimeLineWidget widget;
	widget.show();
#else
	MainWindow w;
	w.show();
#endif

	return a.exec();
}
