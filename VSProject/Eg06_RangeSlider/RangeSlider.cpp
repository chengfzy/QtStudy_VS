#include "RangeSlider.h"

RangeSlider::RangeSlider(QWidget *parent)
	: QSlider(parent)
{
	m_pDisplayLabel = new QLabel(this);
	m_pDisplayLabel->setFixedSize(20, 20);
	m_pDisplayLabel->setAlignment(Qt::AlignCenter);
	m_pDisplayLabel->setVisible(true);
	m_pDisplayLabel->move(0, -10);

}

RangeSlider::RangeSlider(Qt::Orientation orientation, QWidget * parent)
	: RangeSlider(parent)
{
	this->setOrientation(orientation);
}

RangeSlider::~RangeSlider()
{
}

void RangeSlider::mousePressEvent(QMouseEvent * event)
{
	if (!m_pDisplayLabel->isVisible())
	{
		m_pDisplayLabel->setVisible(true);
		m_pDisplayLabel->setText(QString::number(this->value()));
	}

	QSlider::mousePressEvent(event);
}

void RangeSlider::mouseReleaseEvent(QMouseEvent * event)
{
	if (m_pDisplayLabel->isVisible())
	{
		m_pDisplayLabel->setVisible(false);
	}

	QSlider::mouseReleaseEvent(event);
}

void RangeSlider::mouseMoveEvent(QMouseEvent * event)
{
	m_pDisplayLabel->setText(QString::number(this->value()));
	m_pDisplayLabel->move((width() - m_pDisplayLabel->width()) * value() / (maximum() - minimum()), -10);

	QSlider::mouseMoveEvent(event);
}
