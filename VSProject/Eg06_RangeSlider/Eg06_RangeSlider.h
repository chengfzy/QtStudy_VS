#pragma once

#include <QtWidgets/QWidget>
#include "RangeSlider.h"

class Eg06_RangeSlider : public QWidget
{
	Q_OBJECT

public:
	Eg06_RangeSlider(QWidget *parent = Q_NULLPTR);

private:
	RangeSlider* m_pRangeSlider;
};
