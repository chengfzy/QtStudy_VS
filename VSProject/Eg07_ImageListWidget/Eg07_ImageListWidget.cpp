#include "Eg07_ImageListWidget.h"

Eg07_ImageListWidget::Eg07_ImageListWidget(QWidget *parent)
	: QMainWindow(parent)
{
	m_pImageListWidget = new ImageListWidget(this);
	QVector<QPixmap> aImage;
	aImage << QPixmap(tr(":/image/1"))
		<< QPixmap(tr(":/image/2"))
		<< QPixmap(tr(":/image/3"))
		<< QPixmap(tr(":/image/4"))
		<< QPixmap(tr(":/image/5"))
		<< QPixmap(tr(":/image/6"))
		<< QPixmap(tr(":/image/7"));
	m_pImageListWidget->SetImages(aImage);

	

	//QWidget* widget = new QWidget(this);
	//QVBoxLayout* mainLayout = new QVBoxLayout(widget);
	////mainLayout->addWidget(pLabel);
	//mainLayout->addWidget(m_pImageListWidget);
	//widget->setLayout(mainLayout);


	setCentralWidget(m_pImageListWidget);
}
