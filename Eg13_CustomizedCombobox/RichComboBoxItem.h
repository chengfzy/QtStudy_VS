#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class RichComboBoxItem : public QWidget
{
	Q_OBJECT

public:
	RichComboBoxItem(const QString& text, QWidget *parent = nullptr);
	~RichComboBoxItem();

signals:
	void itemClicked(const QString& text) const;

public:
	QString itemString() const;
	void setLabelString(const QString& labelStr);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	QLabel* m_pLabel;
	QPushButton* m_pButton;

	bool m_bMousePressed;
};
