#pragma once

#include <QtWidgets/QMainWindow>
#include "CropWidget.h"
#include <QtWidgets>

class Eg03_ImageCrop : public QMainWindow
{
	Q_OBJECT

public:
	Eg03_ImageCrop(QWidget *parent = Q_NULLPTR);

private:
	CropWidget* m_pCropWidget;
	QLabel* m_pLabel;
};
