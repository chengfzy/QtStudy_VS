#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>

class Eg09_Scroll : public QMainWindow
{
	Q_OBJECT

public:
	Eg09_Scroll(QWidget *parent = Q_NULLPTR);

	void AddButton();

private:
	QHBoxLayout* buttonLayout;
	QScrollArea* scrollArea;
	QPushButton* addButton;
};
