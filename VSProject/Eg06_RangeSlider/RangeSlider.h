#pragma once

#include <QSlider>
#include <QLabel>

class RangeSlider : public QSlider
{
public:
	explicit RangeSlider(QWidget *parent = nullptr);
	explicit RangeSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
	~RangeSlider();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	QLabel* m_pDisplayLabel;			//show the text
};
