#include "Eg01_EditablePicture.h"
#include <QVBoxLayout>

Eg01_EditablePicture::Eg01_EditablePicture(QWidget *parent)
	: QWidget(parent)
{
	m_pImage = new QPixmap(tr(":/imge/image"));

	//Image Widget
	m_pImageWidget = new QWidget();

	//Image Label
	m_pImageLabel = new QLabel("Image", m_pImageWidget);

	m_pImageLabel->setPixmap(*m_pImage);
	m_pImageLabel->setAlignment(Qt::AlignCenter);

	//picture widget
	m_pPictureWidget = new PictureWidget();
	m_pPictureWidget->SetImage(*m_pImage);
	m_pPictureWidget->SetLogo(QPixmap(tr(":/imge/logo")));
	
	QHBoxLayout* mainLayout = new QHBoxLayout();
	mainLayout->addWidget(m_pImageWidget);
	mainLayout->addWidget(m_pPictureWidget);

	setLayout(mainLayout);
	setMinimumSize(300, 300);
}

void Eg01_EditablePicture::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);

	m_pImageLabel->resize(m_pImageWidget->size());

	QPixmap image = m_pImage->scaled(m_pImageLabel->size(), Qt::KeepAspectRatio);
	m_pImageLabel->setPixmap(image);
}
