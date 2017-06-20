#include "Eg12_FramePreview.h"
#include <QtWidgets>

Eg12_FramePreview::Eg12_FramePreview(QWidget *parent)
	: QMainWindow(parent)
{
	//m_pThumbnailLabel = new ThumbnailLabel();
	//QGraphicsScene* pScene = new QGraphicsScene(this);
	//QGraphicsView* pView = new QGraphicsView(pScene, this);

	m_pThumbnailStrip = new ThumbnailStrip(this);
	//m_pThumbnailStrip->setMinimumSize(1500, 400);
	m_pThumbnailStrip->setMinimumHeight(100);

	QPushButton* pButton = new QPushButton("Load Images", this);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_pThumbnailStrip);
	mainLayout->addWidget(pButton);

	QWidget* pWidget = new QWidget(this);
	pWidget->setLayout(mainLayout);

	setCentralWidget(pWidget);

	//actions
	connect(pButton, &QPushButton::clicked, this, &Eg12_FramePreview::loadImages);
}

void Eg12_FramePreview::loadImages()
{
	QStringList imageFiles = QFileDialog::getOpenFileNames(this, "Load Images", QString(), "Images (*.png, *.jpg)");
	
	QList<QPixmap*> images;
	for (auto file : imageFiles)
	{
		images.push_back(new QPixmap(file));
		//ThumbnailLabel* pLabel = new ThumbnailLabel();
		//pLabel->setPixmap(image);
	}


	m_pThumbnailStrip->setImages(images);
}
