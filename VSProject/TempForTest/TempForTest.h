#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>

class TempForTest : public QMainWindow
{
	Q_OBJECT

public:
	TempForTest(QWidget *parent = Q_NULLPTR);

private:
	void changeLabel(int value);

private:
	QLabel* label;
	QSlider* slider;
};
