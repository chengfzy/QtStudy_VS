#include "ThumbnailStrip.h"

ThumbnailStrip::ThumbnailStrip(QWidget *parent)
	: QWidget(parent)
{
	ThumbnailFrame* pFrame = new ThumbnailFrame();
	m_pScene = new QGraphicsScene(this); // move scene to view class?
	pFrame->view()->setScene(m_pScene);
	pFrame->setFrameShape(QFrame::NoFrame);


	QBoxLayout* mainLayout = new QBoxLayout(QBoxLayout::BottomToTop);
	mainLayout->setSpacing(0);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addWidget(pFrame);

	setLayout(mainLayout);
}

ThumbnailStrip::~ThumbnailStrip()
{
}

void ThumbnailStrip::setImages(const QList<QPixmap*>& images)
{
	double size = 100;
	static int i{ 0 };

	//m_apThumbnailLabels.clear();
	for (auto image : images)
	{
		QPixmap* pImage = new QPixmap(image->scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation));

		ThumbnailLabel* pLabel = new ThumbnailLabel();
		pLabel->setPixmap(*pImage);
		pLabel->setPos(i++ * 110, 0);

		m_pScene->addItem(pLabel);
		m_apThumbnailLabels.push_back(pLabel);
	}

	update();
}
