#include "ThumbnailFrame.h"

ThumbnailFrame::ThumbnailFrame(QWidget *parent)
	: QFrame(parent)
{
	setFocusPolicy(Qt::NoFocus);
	m_pGraphicsView = new ThumbnailGraphicsView(this);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(m_pGraphicsView);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
}

ThumbnailFrame::~ThumbnailFrame()
{
}

ThumbnailGraphicsView *ThumbnailFrame::view() const
{
	return m_pGraphicsView;
}

void ThumbnailFrame::addItem(QGraphicsItem *item) 
{
	m_pGraphicsView->scene()->addItem(item);
}

void ThumbnailFrame::acceptThumbnailClick(int num)
{
	emit thumbnailClicked(num);
}