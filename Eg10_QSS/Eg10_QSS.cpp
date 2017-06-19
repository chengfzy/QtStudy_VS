#include "Eg10_QSS.h"
#include <QtWidgets>

Eg10_QSS::Eg10_QSS(QWidget *parent)
	: QMainWindow(parent)
{
	//apply qss style
	QFile file(tr(":/qss/main"));
	file.open(QFile::ReadOnly);
	QTextStream filetext(&file);
	QString styleSheet = filetext.readAll();
	this->setStyleSheet(styleSheet);
	file.close();

	//widget
	QLabel* label = new QLabel("Label", this);
	QPushButton* button = new QPushButton("Button", this);

	//main layout
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(label);
	mainLayout->addWidget(button);

	//main widget
	QWidget* mainWidget = new QWidget(this);
	mainWidget->setLayout(mainLayout);

	setCentralWidget(mainWidget);
}
