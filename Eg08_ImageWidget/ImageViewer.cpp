#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent)
	: QWidget(parent)
{
}

ImageViewer::~ImageViewer()
{
}

void ImageViewer::SetImage(const QPixmap & image)
{
	m_image = image;
}

void ImageViewer::paintEvent(QPaintEvent * event)
{
	QWidget::paintEvent(event);

	if (m_image.isNull())
		return;

	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	QSize pixSize = m_image.size();
	pixSize.scale(event->rect().size(), Qt::KeepAspectRatio);

	QPoint topleft;
	topleft.setX((this->width() - pixSize.width()) / 2);
	topleft.setY((this->height() - pixSize.height()) / 2);

	painter.drawPixmap(topleft, m_image.scaled(pixSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
