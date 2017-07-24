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

	//track label layout
	m_pTrackLabelLayout = new QVBoxLayout();
	m_pTrackLabelLayout->addWidget(new TrackLabelTopFiller());

	//track editor layout
	m_pTrackEditorLayout = new QVBoxLayout();
	m_pTrackEditorLayout->addWidget(m_pRule);
	m_pTrackEditorLayout->addStretch();
	//m_pTrackEditorLayout->setSpacing(0);
	m_pTrackEditorLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);

	//track layout
	QHBoxLayout* pTrackLayout = new QHBoxLayout();
	pTrackLayout->addLayout(m_pTrackLabelLayout);
	pTrackLayout->addLayout(m_pTrackEditorLayout);
	pTrackLayout->setSpacing(0);
	pTrackLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);

	//track container widget
	m_pTrackContainerWidget = new QWidget();
	m_pTrackContainerWidget->setLayout(pTrackLayout);
	//track scroll area
	QScrollArea* pTrackScrollArea = new QScrollArea();
	pTrackScrollArea->setWidget(m_pTrackContainerWidget);
	//pTrackScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pTrackScrollArea->setFrameShape(QFrame::NoFrame);

	//main layout
	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(pToolBar);
	//pMainLayout->addLayout(pTrackLayout);
	pMainLayout->addWidget(pTrackScrollArea);

	this->setLayout(pMainLayout);
}

void TimeLineWidget::setCurrentFrame(int frame)
{
	m_pRule->setCurrentFrame(frame);
	for (auto pTrackEditor : m_apTrack)
		pTrackEditor.pEditor->setCurrentFrame(frame);
}

void TimeLineWidget::setFrameStep(int step)
{
	m_pRule->setFrameStep(step);
	for (auto pTrackEditor : m_apTrack)
		pTrackEditor.pEditor->setFrameStep(step);
}

void TimeLineWidget::addTrack()
{
	removeTrackFromScroll();

	//add track label
	TrackLabel* pTrackLabel = new TrackLabel("Step01");

	//add track editor
	TrackEditor* pTrackEditor = new TrackEditor(QTime(0, 0, 1), 1000);
	pTrackEditor->setStartFrame(100);
	pTrackEditor->setEndFrame(500);
	pTrackEditor->setFrameStep(m_pRule->frameStep());
	pTrackEditor->setTitle("New Logo Track");
	QPixmap startFrame("D:/Code/Data/spring01.jpg");
	QPixmap endFrame("D:/Code/Data/spring02.jpg");
	pTrackEditor->setStartFrameImage(startFrame);
	pTrackEditor->setEndFrameImage(endFrame);
	connect(pTrackEditor, &TrackEditor::currentFrameChanged, m_pRule, &TimeLineRule::currentFrameChanged);
	connect(pTrackEditor, &TrackEditor::trackSelected, this, &TimeLineWidget::udpateSelectTrack);


	m_apTrack.push_back(Track(pTrackLabel, pTrackEditor));
	updateTrackWidget();
}

void TimeLineWidget::removeTrack()
{
	QVector<Track>::iterator it = m_apTrack.begin();
	for (; it != m_apTrack.end(); ++it)
	{
		if (it->pEditor->isSelected())
			break;
	}
	if (it != m_apTrack.end())
	{
		removeTrackFromScroll();
		TrackLabel* pLabel = it->pLabel;
		TrackEditor* pEditor = it->pEditor;
		m_apTrack.erase(it);
		updateTrackWidget();
		delete pLabel;
		delete pEditor;
		update();
	}
}

// remove all track from scroll area
void TimeLineWidget::removeTrackFromScroll()
{
	for (int i = 0; i < m_pTrackLabelLayout->count(); ++i)
	{
		m_pTrackLabelLayout->removeItem(m_pTrackLabelLayout->itemAt(i));
	}
	for (int i = 0; i < m_pTrackEditorLayout->count(); ++i)
	{
		m_pTrackEditorLayout->removeItem(m_pTrackEditorLayout->itemAt(i));
	}
	update();
}

void TimeLineWidget::updateTrackWidget()
{
	int height = m_pRule->height();
	m_pTrackEditorLayout->addWidget(m_pRule);
	for (auto pTrack : m_apTrack)
	{
		m_pTrackLabelLayout->addWidget(pTrack.pLabel);
		m_pTrackEditorLayout->addWidget(pTrack.pEditor);
		height += pTrack.pEditor->height();
	}
	m_pTrackEditorLayout->addStretch();
	m_pTrackEditorLayout->setSpacing(0);
	m_pTrackContainerWidget->setFixedHeight(height);
	update();
}

void TimeLineWidget::udpateSelectTrack()
{
	TrackEditor* pTrackEditor = qobject_cast<TrackEditor*>(sender());
	int index = 0;
	for (; index < m_apTrack.size(); ++index)
	{
		if (pTrackEditor != m_apTrack[index].pEditor)
			m_apTrack[index].pEditor->setSelected(false);
	}
}
