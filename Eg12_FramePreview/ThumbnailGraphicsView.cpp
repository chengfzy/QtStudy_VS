#include "ThumbnailGraphicsView.h"
#include "ThumbnailFrame.h"

ThumbnailGraphicsView::ThumbnailGraphicsView(ThumbnailFrame* frame)
	: QGraphicsView(), m_pFrame(frame)
{
	setFocusPolicy(Qt::NoFocus);
	setAlignment(Qt::AlignLeft | Qt::AlignTop);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

	QScrollBar* scrollBar = horizontalScrollBar();
	connect(scrollBar, &QScrollBar::sliderMoved, this, &ThumbnailGraphicsView::scrolled);
	connect(this, &ThumbnailGraphicsView::scrolled, m_pFrame, &ThumbnailFrame::scrolled);
}

ThumbnailGraphicsView::~ThumbnailGraphicsView()
{
}

void ThumbnailGraphicsView::wheelEvent(QWheelEvent * event)
{
	event->accept();
	viewportCenter = mapToScene(viewport()->rect().center());

	// on some systems pixelDelta() returns non-zero values with mouse wheel
	// that's why smoothScroll flag workaround
	//if (event->pixelDelta().y() != 0)
	{
		// pixel scrolling (precise)
		centerOnX(viewportCenter.x() - event->pixelDelta().y());
		emit scrolled();
	}	
}

void ThumbnailGraphicsView::centerOnX(int x)
{
	centerOn(x, viewportCenter.y());
}
