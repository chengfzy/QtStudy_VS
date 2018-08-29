#pragma once

#include <QtWidgets>
#include "TimeLineRule.h"
#include "Track.h"


class TimeLineWidget : public QWidget
{
	Q_OBJECT

public:
	TimeLineWidget(QWidget *parent = nullptr);
	~TimeLineWidget();

private:
	void setupUI();
	void setCurrentFrame(int frame);
	void setFrameStep(int step);
	// add track
	void addTrack();
	// remove track
	void removeTrack();

	// remove all track from scroll area
	void removeTrackFromScroll();
	void updateTrackWidget();
	// update track when selected is changed
	void udpateSelectTrack();

private:
	TimeLineRule* m_pRule;						//time line rule
	QVector<Track*> m_apTrack;					//track list

	int m_nFrameNum;							//frame number

	QSlider* m_pScaleSlider;
	QVBoxLayout* m_pTrackLayout;
	QWidget* m_pTrackContainerWidget;
};
