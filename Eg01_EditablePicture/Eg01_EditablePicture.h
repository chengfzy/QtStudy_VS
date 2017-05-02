#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include "PictureWidget.h"

class Eg01_EditablePicture : public QWidget
{
	Q_OBJECT

public:
	Eg01_EditablePicture(QWidget *parent = Q_NULLPTR);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QPixmap* m_pImage;
	QWidget* m_pImageWidget;
	QLabel* m_pImageLabel;
	PictureWidget* m_pPictureWidget;
};
