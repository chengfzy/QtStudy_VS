#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include "ImageCropper.h"

class Eg05_ImageCrop : public QWidget
{
	Q_OBJECT

public:
	Eg05_ImageCrop(QWidget *parent = Q_NULLPTR);

private:
	QLabel* m_pImageLabel;
	ImageCropper* m_imageCropper;
};
