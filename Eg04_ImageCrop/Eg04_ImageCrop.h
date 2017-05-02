#pragma once

#include <QtWidgets/QMainWindow>
#include "imagecropper.h"
#include "QtWidgets"

class Eg04_ImageCrop : public QWidget
{
	Q_OBJECT
public:
	explicit Eg04_ImageCrop(QWidget* _parent = nullptr);

signals:

private slots :
	void crop();

private:
	ImageCropper* m_imageCropper;
	QLabel* m_croppedImage;
};
