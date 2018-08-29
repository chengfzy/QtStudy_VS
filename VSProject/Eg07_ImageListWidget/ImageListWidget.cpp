#include "ImageListWidget.h"

ImageListWidget::ImageListWidget(QWidget *parent)
	: QWidget(parent)
{
	//image label
	m_pImageLayout = new QHBoxLayout();
	//for (int i = 0; i < 5; ++i)
	//{
	//	m_apImageLabel << new QLabel("Image", this);
	//}
	//for(auto pLabel: m_apImageLabel)
	//{
	//	m_pImageLayout->addWidget(pLabel);
	//}

	////image widget
	//QWidget* widget = new QWidget(this);
	//widget->setLayout(m_pImageLayout);

	////image scroll
	//QScrollArea* imageScroll = new QScrollArea(this);
	//imageScroll->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	//imageScroll->setWidget(widget);

	////main layout
	//QVBoxLayout* mainLayout = new QVBoxLayout(this);
	//mainLayout->addWidget(imageScroll);
	//setLayout(mainLayout);

	setMaximumHeight(500);
	
}

ImageListWidget::~ImageListWidget()
{
}

void ImageListWidget::SetImages(const QVector<QPixmap>& apImage)
{
	for (auto image : apImage)
	{
		QLabel* pLabel = new QLabel("Image", this);
		pLabel->setPixmap(image.scaledToHeight(300));

		m_apImageLabel << pLabel;

		pLabel->setScaledContents(true);
		m_pImageLayout->addWidget(pLabel);
	}

	QWidget* widget = new QWidget(this);
	widget->setLayout(m_pImageLayout);

	//image scroll
	QScrollArea* imageScroll = new QScrollArea(this);
	imageScroll->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	imageScroll->setWidget(widget);
	imageScroll->setAlignment(Qt::AlignCenter);

	//main layout
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(imageScroll);
	setLayout(mainLayout);

	update();
}
