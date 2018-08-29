#pragma once

#include <QtWidgets/QMainWindow>
#include <QComboBox>
#include "RichComboBox.h"

class Eg13_CustomizedCombobox : public QMainWindow
{
	Q_OBJECT

public:
	Eg13_CustomizedCombobox(QWidget *parent = Q_NULLPTR);

private:
	void showItem(const QString& itemText);

	void updateComboItem(int index);

private:
	RichComboBox* m_pRichComboBox;
	QComboBox* m_pComboBox;
};
