#pragma once

#include <QtWidgets/QMainWindow>
#include "ImageListWidget.h"

class Eg07_ImageListWidget : public QMainWindow
{
	Q_OBJECT

public:
	Eg07_ImageListWidget(QWidget *parent = Q_NULLPTR);

private:
	ImageListWidget* m_pImageListWidget;
};
