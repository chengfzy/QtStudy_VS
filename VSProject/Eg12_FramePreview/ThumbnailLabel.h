#pragma once

#include <QObject>
#include <QtWidgets>

class ThumbnailLabel : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	explicit ThumbnailLabel();
	~ThumbnailLabel();

	void setPixmap(const QPixmap& image);


	QRectF boundingRect() const override;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
	QPixmap* m_pPixmap;
};
