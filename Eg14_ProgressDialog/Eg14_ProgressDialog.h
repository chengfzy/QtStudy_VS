#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>

class Eg14_ProgressDialog : public QDialog
{
	Q_OBJECT

public:
	Eg14_ProgressDialog(QWidget *parent = Q_NULLPTR);

	void startProgress();
private:
	QProgressBar* m_pProgressBar;
	QPushButton* m_pStartButton;
};
