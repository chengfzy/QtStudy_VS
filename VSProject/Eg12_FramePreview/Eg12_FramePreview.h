#pragma once

#include <QtWidgets/QMainWindow>
#include "ThumbnailStrip.h"

class Eg12_FramePreview : public QMainWindow
{
	Q_OBJECT

public:
	Eg12_FramePreview(QWidget *parent = Q_NULLPTR);

	void loadImages();

private:
	ThumbnailStrip* m_pThumbnailStrip;
	ThumbnailLabel* m_pThumbnailLabel;
};
