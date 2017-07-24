#pragma once

#include <QtWidgets>

class TrackLabel : public QWidget
{
	Q_OBJECT

public:
	TrackLabel(QString title = "Step", QWidget *parent = nullptr);
	~TrackLabel();

private:
	void setupUI();

private:
	QString m_szTitle;
	QLabel* m_pTitleLabel;
};
