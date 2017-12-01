#include <QtWidgets/QApplication>
#include "LogWidget.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	LogWidget* logWidget = new LogWidget();
	logWidget->show();

	QTimer* timer = new QTimer();
	QObject::connect(timer, &QTimer::timeout, []() {
		static int n{ 0 };
		cout << "[" << to_string(n) << "] print by cout" << endl;
		cerr << "[" << to_string(n) << "] print by cerr" << endl;
		clog << "[" << to_string(n) << "] print by clog" << endl;
		++n;
	});

	timer->start(1000);

	return a.exec();
}
