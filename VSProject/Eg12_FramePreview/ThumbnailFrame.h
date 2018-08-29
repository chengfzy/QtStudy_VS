#pragma once

#include <QtWidgets>
#include "ThumbnailGraphicsView.h"

class ThumbnailFrame : public QFrame
{
	Q_OBJECT

public:
	explicit ThumbnailFrame(QWidget *parent = nullptr);
	~ThumbnailFrame();

	ThumbnailGraphicsView* view() const;
	void addItem(QGraphicsItem* item);
	void acceptThumbnailClick(int);

signals:
	void thumbnailClicked(int);
	void scrolled();

private:
	ThumbnailGraphicsView* m_pGraphicsView;
};
