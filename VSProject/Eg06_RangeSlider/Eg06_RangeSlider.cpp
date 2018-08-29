#include "Eg06_RangeSlider.h"
#include <QtWidgets>

Eg06_RangeSlider::Eg06_RangeSlider(QWidget *parent)
	: QWidget(parent)
{
	m_pRangeSlider = new RangeSlider(Qt::Horizontal, this);
	m_pRangeSlider->setRange(0, 10);
	m_pRangeSlider->setTickInterval(1);
	m_pRangeSlider->setTickPosition(QSlider::TickPosition::TicksAbove);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_pRangeSlider);

	setLayout(layout);
}
