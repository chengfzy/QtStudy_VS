#pragma once

#include <QtWidgets>

class ImageListWidget : public QWidget
{
	Q_OBJECT

public:
	ImageListWidget(QWidget *parent);
	~ImageListWidget();

	void SetImages(const QVector<QPixmap>& apImage);

private:
	QVector<QLabel*> m_apImageLabel;
	QHBoxLayout* m_pImageLayout;
};
