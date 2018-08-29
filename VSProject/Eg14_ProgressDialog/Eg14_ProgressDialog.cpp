#include "Eg14_ProgressDialog.h"

Eg14_ProgressDialog::Eg14_ProgressDialog(QWidget *parent)
	: QDialog(parent)
{
	m_pProgressBar = new QProgressBar(this);

	m_pStartButton = new QPushButton("Start", this);

	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_pProgressBar);
	mainLayout->addWidget(m_pStartButton);

	setLayout(mainLayout);
	
	connect(m_pStartButton, &QPushButton::clicked, this, &Eg14_ProgressDialog::startProgress);
}

void Eg14_ProgressDialog::startProgress()
{
	int maxNum = 120000;
	//m_pProgressBar->setRange(0, maxNum);
	//for (int i = 1; i <= maxNum; ++i)
	//	m_pProgressBar->setValue(i);

	QProgressDialog* processDlg = new QProgressDialog(this);
	processDlg->setWindowModality(Qt::WindowModal);
	processDlg->setWindowTitle(tr("Please wait"));
	processDlg->setLabelText(tr("copy"));
	processDlg->setRange(0, maxNum);

	for (int i = 1; i <= maxNum; ++i)
		processDlg->setValue(i);
}
