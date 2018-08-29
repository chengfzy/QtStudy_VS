#pragma once

#include <QtWidgets>

class ThumbnailFrame;

class ThumbnailGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	explicit ThumbnailGraphicsView(ThumbnailFrame* frame);
	~ThumbnailGraphicsView();

protected:
	void wheelEvent(QWheelEvent* event) override;

signals:
	void scrolled();

private:
	void centerOnX(int x);

private:
	ThumbnailFrame* m_pFrame;
	QPointF viewportCenter;
};
