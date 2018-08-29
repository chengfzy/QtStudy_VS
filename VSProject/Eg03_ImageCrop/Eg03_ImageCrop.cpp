#include "Eg03_ImageCrop.h"

Eg03_ImageCrop::Eg03_ImageCrop(QWidget *parent)
	: QMainWindow(parent)
{
	m_pCropWidget = new CropWidget(this);
	m_pLabel = new QLabel(this);

	QPixmap pic;
	pic.load(".\\Resources\\spring.jpg");
	pic.scaledToWidth(100);
	pic.scaledToHeight(200);
	if (!pic.isNull())
	{
		m_pLabel->setText("hahaha");
		m_pLabel->setPixmap(pic);

		//QPixmap scaledPix = pic.scaled(m_pLabel->width(), m_pLabel->height());
		//m_pLabel->setPixmap(scaledPix);
	}
	
	setCentralWidget(m_pLabel);

	m_pCropWidget->show();
}
