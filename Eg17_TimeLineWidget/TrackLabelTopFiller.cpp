#include "TrackLabelTopFiller.h"
#include <QPainter>

TrackLabelTopFiller::TrackLabelTopFiller(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(100, 30);
}

TrackLabelTopFiller::~TrackLabelTopFiller()
{
}

void TrackLabelTopFiller::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);

	//draw backgroud rect
	painter.save();
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(Qt::darkGray));
	painter.drawRect(this->rect());
	painter.restore();
}
