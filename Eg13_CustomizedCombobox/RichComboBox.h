#pragma once

#include <QComboBox>
#include <RichComboBoxItem.h>
#include <QtWidgets>

class RichComboBox : public QComboBox
{
	Q_OBJECT

public:
	RichComboBox(QWidget *parent = nullptr);
	~RichComboBox();

	void addItem(RichComboBoxItem* item);

protected:

private:
	void setShowText(const QString& text);
	//void setText()

private:
	QListWidget* m_pListWidget;
	QLineEdit* m_pLineEdit;
};
