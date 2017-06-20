#pragma once

#include <QtWidgets>
#include "ThumbnailFrame.h"
#include "ThumbnailLabel.h"

class ThumbnailStrip : public QWidget
{
	Q_OBJECT

public:
	explicit ThumbnailStrip(QWidget *parent = nullptr);
	~ThumbnailStrip();

	void setImages(const QList<QPixmap*>& images);

private:
	QGraphicsScene* m_pScene;
	QGraphicsView* m_pView;
	QList<ThumbnailLabel*> m_apThumbnailLabels;
};
