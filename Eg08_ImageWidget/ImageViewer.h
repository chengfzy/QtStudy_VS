#pragma once

#include <QWidget>
#include <QtWidgets>

class ImageViewer : public QWidget
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = nullptr);
	~ImageViewer();


	void SetImage(const QPixmap& image);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QWidget* m_pWidget;
	QPixmap m_image;
};
