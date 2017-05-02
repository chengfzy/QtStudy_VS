#pragma once

#include <QtWidgets>

class ShowPicture : public QWidget
{
	Q_OBJECT

public:
	ShowPicture(QWidget *parent = nullptr);
	~ShowPicture(); 

protected:
		bool eventFilter(QObject *, QEvent *) override;
private:
	QLabel* m_pLabel;
};
