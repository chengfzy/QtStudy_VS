#pragma once

#include <QtWidgets>
#include "TimeLineRule.h"
#include "TrackLabel.h"
#include "TrackLabelTopFiller.h"
#include "TrackEditor.h"


class TimeLineWidget : public QWidget
{
	Q_OBJECT

private:
	struct Track
	{
		Track(TrackLabel* pLabel = nullptr, TrackEditor* pEditor = nullptr)
			: pLabel(pLabel), pEditor(pEditor)
		{}

		TrackLabel* pLabel;
		TrackEditor* pEditor;
	};

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
	QVector<Track> m_apTrack;					//track list
	//TrackEditor* m_pTrackEditor;				//track editor

	int m_nFrameNum;			//frame number

	int m_nShowStartFrame;		//the start frame shown
	int m_nFrameStep;			//frame step to draw the rule

	QSlider* m_pScaleSlider;
	TrackLabelTopFiller* m_pTrackLabelTopFiller;
	QVBoxLayout* m_pTrackLabelLayout;
	QVBoxLayout* m_pTrackEditorLayout;
	QWidget* m_pTrackContainerWidget;

};
