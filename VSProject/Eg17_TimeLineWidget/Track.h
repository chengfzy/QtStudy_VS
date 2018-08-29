#pragma once

#include "TimeLineRule.h"

class Track : public TimeLineRule
{
	Q_OBJECT

public:
	Track(QTime duration = QTime(), int frameNum = 0, QWidget *parent = nullptr);
	~Track();

public:
	int startFrame() const;
	int endFrame() const;
	QString title() const;
	bool isSelected() const;

public:
	void setStartFrame(int frame);
	void setEndFrame(int frame);
	void setTitle(const QString& title);
	void setStartFrameImage(const QPixmap& image);
	void setEndFrameImage(const QPixmap& image);
	void setSelected(bool selected = true);
	// move region with delta frame
	void moveRegion(int deltaFrame);

signals:
	void trackSelected() const;
	void startFrameChanged(int frame) const;
	void endFrameChanged(int frame) const;

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	int m_nStartFrame;				//start frame
	int m_nEndFrame;				//end frame
	QString m_szTitle;				//track title
	QPixmap m_startFrameThumb;		//thumbnail in start frame
	QPixmap m_endFrameThumb;		//thumbnail in end frame

	bool m_bSelected;				//indict whether the track is selected
	bool m_bAdjustStart;			//indict whether mouse is adjust start frame position
	bool m_bAdjustEnd;				//indict whether mouse is adjust end frame position
	bool m_bMouseDrag;				//indict whether mouse is drag widget
	QPoint m_mousePos;				//mouse position
};
