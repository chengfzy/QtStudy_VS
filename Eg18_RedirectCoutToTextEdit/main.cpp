#include <QtWidgets/QApplication>
#include <QtWidgets>
#include "StandardOutputRedirector.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTextEdit* textEdit = new QTextEdit("MyTextEdit");
	textEdit->setFixedSize(400, 300);
	StandardOutputRedirector redirector(std::cout, textEdit);
	textEdit->show();

	cout << "Send this to Text Edit1" << endl;
	cout << "Send this to Text Edit2" << endl;


	return a.exec();
}
