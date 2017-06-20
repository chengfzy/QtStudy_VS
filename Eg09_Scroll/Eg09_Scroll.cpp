#include "Eg09_Scroll.h"

Eg09_Scroll::Eg09_Scroll(QWidget *parent)
	: QMainWindow(parent)
{
	buttonLayout = new QHBoxLayout(this);
	for (int i = 0; i < 10; ++i)
	{
		QPushButton* button = new QPushButton("Button" + QString::number(i), this);
		buttonLayout->addWidget(button);
	}

	//button widget
	QWidget* buttonWidget = new QWidget(this);
	buttonWidget->setLayout(buttonLayout);

	//scroll area
	scrollArea = new QScrollArea(this);
	scrollArea->setWidget(buttonWidget);

	//button
	addButton = new QPushButton("Add Button", this);

	//main layout
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(scrollArea);
	mainLayout->addWidget(addButton);

	//main widget
	QWidget* mainWidget = new QWidget(this);
	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);

	connect(addButton, &QPushButton::clicked, this, &Eg09_Scroll::AddButton);
}

void Eg09_Scroll::AddButton()
{
	QPushButton* button = new QPushButton("Button Added", this);
	//button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	buttonLayout->addWidget(button);

	//button widget
	QWidget* buttonWidget = new QWidget(this);
	buttonWidget->setLayout(buttonLayout);

	//scroll area
	scrollArea->setWidget(buttonWidget);
}
