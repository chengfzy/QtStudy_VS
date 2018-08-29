#include "TimeLineWidget.h"

TimeLineWidget::TimeLineWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pRule = new TimeLineRule(QTime(0, 0, 1), 1000);
	setupUI();
}

TimeLineWidget::~TimeLineWidget()
{
}

void TimeLineWidget::setupUI()
{
	//add track action
	QAction* pAddTrackAction = new QAction("Add Track");
	connect(pAddTrackAction, &QAction::triggered, this, &TimeLineWidget::addTrack);

	//remove track action
	QAction* pRemoveTrackAction = new QAction("Remove Track");
	connect(pRemoveTrackAction, &QAction::triggered, this, &TimeLineWidget::removeTrack);

	//current frame spixbox
	QSpinBox* pCurrentFrameSpinBox = new QSpinBox();
	pCurrentFrameSpinBox->setRange(1, m_pRule->frameNumber());
	pCurrentFrameSpinBox->setValue(m_pRule->currentFrame());
	connect(m_pRule, &TimeLineRule::currentFrameChanged, pCurrentFrameSpinBox, &QSpinBox::setValue);
	connect(pCurrentFrameSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &TimeLineWidget::setCurrentFrame);

	//zoom out action
	QAction* pZoomOutAction = new QAction("Zoom Out");
	connect(pZoomOutAction, &QAction::triggered, m_pRule, &TimeLineRule::zoomOut);
	//zoom in action
	QAction* pZoomInAction = new QAction("Zoom In");
	connect(pZoomInAction, &QAction::triggered, m_pRule, &TimeLineRule::zoomIn);
	//slider
	m_pScaleSlider = new QSlider(Qt::Horizontal);
	m_pScaleSlider->setRange(-m_pRule->maxFrameStep(), -m_pRule->minFrameStep());
	m_pScaleSlider->setValue(-m_pRule->frameStep());
	m_pScaleSlider->setFixedWidth(200);
	connect(m_pRule, &TimeLineRule::frameStepChanged, this, [&](int step)
	{
		m_pScaleSlider->setValue(-step);
	});
	connect(m_pScaleSlider, &QSlider::valueChanged, this, [&](int value)
	{
		this->setFrameStep(-value);
	});

	//tool bar
	QToolBar* pToolBar = new QToolBar();
	pToolBar->addAction(pAddTrackAction);
	pToolBar->addAction(pRemoveTrackAction);
	pToolBar->addWidget(pCurrentFrameSpinBox);
	pToolBar->addAction(pZoomOutAction);
	pToolBar->addWidget(m_pScaleSlider);
	pToolBar->addAction(pZoomInAction);

	//track editor layout
	m_pTrackLayout = new QVBoxLayout();
	m_pTrackLayout->addWidget(m_pRule);
	m_pTrackLayout->addStretch();
	m_pTrackLayout->setSpacing(0);
	m_pTrackLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);

	//track container widget
	m_pTrackContainerWidget = new QWidget();
	m_pTrackContainerWidget->setLayout(m_pTrackLayout);
	//track scroll area
	QScrollArea* pTrackScrollArea = new QScrollArea();
	pTrackScrollArea->setWidget(m_pTrackContainerWidget);
	pTrackScrollArea->setFrameShape(QFrame::NoFrame);

	//main layout
	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(pToolBar);
	pMainLayout->addWidget(pTrackScrollArea);

	this->setLayout(pMainLayout);
}

void TimeLineWidget::setCurrentFrame(int frame)
{
	m_pRule->setCurrentFrame(frame);
	for (auto pTrackEditor : m_apTrack)
		pTrackEditor->setCurrentFrame(frame);
}

void TimeLineWidget::setFrameStep(int step)
{
	m_pRule->setFrameStep(step);
	for (auto pTrackEditor : m_apTrack)
		pTrackEditor->setFrameStep(step);
}

void TimeLineWidget::addTrack()
{
	removeTrackFromScroll();
	
	//add track editor
	Track* pTrack = new Track(QTime(0, 0, 1), 1000);
	pTrack->setStartFrame(100);
	pTrack->setEndFrame(500);
	pTrack->setFrameStep(m_pRule->frameStep());
	pTrack->setTitle("Step01");
	QPixmap startFrame("D:/Code/Data/spring01.jpg");
	QPixmap endFrame("D:/Code/Data/spring02.jpg");
	pTrack->setStartFrameImage(startFrame);
	pTrack->setEndFrameImage(endFrame);
	connect(pTrack, &Track::currentFrameChanged, m_pRule, &TimeLineRule::currentFrameChanged);
	connect(pTrack, &Track::trackSelected, this, &TimeLineWidget::udpateSelectTrack);
	
	m_apTrack.push_back(pTrack);
	updateTrackWidget();
}

void TimeLineWidget::removeTrack()
{
	QVector<Track*>::iterator it = m_apTrack.begin();
	for (; it != m_apTrack.end(); ++it)
	{
		if ((*it)->isSelected())
			break;
	}
	if (it != m_apTrack.end())
	{
		removeTrackFromScroll();
		Track* pEditor = *it;
		m_apTrack.erase(it);
		updateTrackWidget();
		delete pEditor;
		update();
	}
}

// remove all track from scroll area
void TimeLineWidget::removeTrackFromScroll()
{
	for (int i = 0; i < m_pTrackLayout->count(); ++i)
	{
		m_pTrackLayout->removeItem(m_pTrackLayout->itemAt(i));
	}
	update();
}

void TimeLineWidget::updateTrackWidget()
{
	int height = m_pRule->height();
	m_pTrackLayout->addWidget(m_pRule);
	for (auto pTrack : m_apTrack)
	{
		m_pTrackLayout->addWidget(pTrack);
		height += pTrack->height();
	}
	m_pTrackLayout->addStretch();
	m_pTrackLayout->setSpacing(0);
	m_pTrackContainerWidget->setFixedHeight(height);
	update();
}

void TimeLineWidget::udpateSelectTrack()
{
	Track* pTrackEditor = qobject_cast<Track*>(sender());
	int index = 0;
	for (; index < m_apTrack.size(); ++index)
	{
		if (pTrackEditor != m_apTrack[index])
			m_apTrack[index]->setSelected(false);
	}
} 