#include "ThumbnailLabel.h"

ThumbnailLabel::ThumbnailLabel()
{
}

ThumbnailLabel::~ThumbnailLabel()
{
}

void ThumbnailLabel::setPixmap(const QPixmap & image)
{
	m_pPixmap = new QPixmap(image);
}

QRectF ThumbnailLabel::boundingRect() const
{
	return QRectF(0, 0, m_pPixmap->width(), m_pPixmap->height());
}

void ThumbnailLabel::paint(QPainter * painter, const QStyleOptionGraphicsItem * item, QWidget * widget)
{
	if (m_pPixmap != nullptr)
	{
		painter->drawPixmap(0, 0, *m_pPixmap);
	}
}
