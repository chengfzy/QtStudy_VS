#include <QtCore/QCoreApplication>
#include <QtXlsx>
#include <iostream>
using namespace std;

void writeXls()
{
	QXlsx::Document xlsx;
	xlsx.write("A1", "Hello Qt Xlsx1");
	xlsx.write("A2", "Hello Qt Xlsx2");
	xlsx.write("A3", "Hello Qt Xlsx3");

	xlsx.saveAs("Test.xlsx");
}

void readXls()
{
	QXlsx::Document xlsx("Test.xlsx");
	cout << "Read File from .xlsx..." << endl;
	cout << xlsx.read("A1").toString().toStdString() << endl;
	cout << xlsx.read("A2").toString().toStdString() << endl;
	cout << xlsx.read("A3").toString().toStdString() << endl;
}

int main(int argc, char *argv[])
{
	writeXls();
	readXls();

	system("pause");
	return 0;
}

