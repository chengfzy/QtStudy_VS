#pragma once

#include <QWidget>
#include <QTime>

class TimeLineRule : public QWidget
{
	Q_OBJECT

public:
	TimeLineRule(QTime duration = QTime(), int frameNum = 0, QWidget *parent = nullptr);
	~TimeLineRule();

public:
	int frameNumber() const;
	int minFrameStep() const;
	int maxFrameStep() const;
	int currentFrame() const;
	int frameStep() const;

public:
	// set frame step
	void setFrameStep(int step);
	/** Zoom in. */
	void zoomIn();
	/** Zoom out. */
	void zoomOut();
	// set current frame
	void setCurrentFrame(int frame);

signals:
	void frameStepChanged(int step) const;
	void currentFrameChanged(int frame) const;

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

protected:
	// get frame at x position
	int positionToFrame(double x);
	// get x position at frame
	double frameToPosition(int frame);

protected:
	QTime m_duration;		//time duration
	int m_nFrameNum;		//frame number
	int m_nCurrentFrame;	//current frame

	int m_nMinFrameStep;	//min frame step
	int m_nMaxFrameStep;	//max frame step
	int m_nFrameStep;		//step in frame(int)

	static const int m_nLabelWidth;		//label width in left
};