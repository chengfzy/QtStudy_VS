#include "TimeLineRule.h"
#include <QtWidgets>

static const int g_nInitialRuleNum = 50;	//20 rules at initialization
static const int g_nInitialWidth = 800;


TimeLineRule::TimeLineRule(QTime duration, int frameNum, QWidget *parent)
	: m_duration(duration), m_nFrameNum(frameNum), m_nCurrentFrame(0)
	, QWidget(parent)
{
	m_nFrameStep = m_nFrameNum / g_nInitialRuleNum;		//20 rules after initialization
	m_nMinFrameStep = 1;
	m_nMaxFrameStep = m_nFrameNum / 10;
	
	setFixedHeight(30);
	setFixedWidth(g_nInitialWidth);
}

TimeLineRule::~TimeLineRule()
{
}


int TimeLineRule::frameNumber() const
{
	return m_nFrameNum;
}

int TimeLineRule::minFrameStep() const
{
	return m_nMinFrameStep;
}

int TimeLineRule::maxFrameStep() const
{
	return m_nMaxFrameStep;
}

int TimeLineRule::currentFrame() const
{
	return m_nCurrentFrame;
}

int TimeLineRule::frameStep() const
{
	return m_nFrameStep;
}


// set frame step
void TimeLineRule::setFrameStep(int step)
{
	if (step < m_nMinFrameStep)
		step = m_nMinFrameStep;
	if (step > m_nMaxFrameStep)
		step = m_nMaxFrameStep;
	if (step != m_nFrameStep)
	{
		setFixedWidth(static_cast<double>(m_nFrameNum) / g_nInitialRuleNum * g_nInitialWidth / step);
		m_nFrameStep = step;
		emit frameStepChanged(m_nFrameStep);
	}
}

/** Zoom in. */
void TimeLineRule::zoomIn()
{
	float newStep = m_nFrameStep / 1.2;
	while (round(newStep) == m_nFrameStep)
		newStep /= 1.2;
	setFrameStep(round(newStep));
}

void TimeLineRule::zoomOut()
{
	float newStep = m_nFrameStep * 1.2;
	while (round(newStep) == m_nFrameStep)
		newStep *= 1.2;
	setFrameStep(round(newStep));
}

// set current frame
void TimeLineRule::setCurrentFrame(int frame)
{
	if (frame > 0 && frame < m_nFrameNum)
	{
		m_nCurrentFrame = frame;
		emit currentFrameChanged(m_nCurrentFrame);
		update();
	}
}

void TimeLineRule::paintEvent(QPaintEvent * event)
{	
	QPainter painter(this);
	const int nTimeRectHeight = height();

	//draw backgroud rect
	painter.save();
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(Qt::darkGray));
	painter.drawRect(this->rect());
	painter.restore();

	//draw time rule
	const int nMaxRuleHeight = nTimeRectHeight * 2 / 3;
	const int nMinRuleHeight = nMaxRuleHeight * 0.5;
	painter.save();
	painter.setPen(QColor(Qt::white));
	for (int n = m_nFrameStep; n < m_nFrameNum; n += m_nFrameStep)
	{
		for (int i = 0; i < 4; ++i)
		{
			painter.drawLine(frameToPosition(n), nTimeRectHeight - nMinRuleHeight, frameToPosition(n), nTimeRectHeight);
			n += m_nFrameStep;
		}
		painter.drawLine(frameToPosition(n), nTimeRectHeight - nMaxRuleHeight, frameToPosition(n), nTimeRectHeight);
		painter.drawText(QPointF(frameToPosition(n) + 2, nTimeRectHeight / 2), QString::number(n));
	}
	painter.restore();

	//draw current frame line
	painter.save();
	const double dCurrentFrameX = frameToPosition(m_nCurrentFrame);
	painter.setPen(QColor(Qt::white));
	painter.drawLine(dCurrentFrameX, 0, dCurrentFrameX, nTimeRectHeight);
	//draw triangle
	painter.setBrush(Qt::white);
	const int nTriangleSize = 4;
	QVector<QPointF> trianglePos{ QPointF(dCurrentFrameX, nTriangleSize * 2),  QPointF(dCurrentFrameX - nTriangleSize, 0), QPointF(dCurrentFrameX + nTriangleSize, 0) };
	painter.drawPolygon(QPolygonF(trianglePos));
	painter.restore();
}

void TimeLineRule::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		setCurrentFrame(positionToFrame(event->pos().x()));
	}
}

void TimeLineRule::mouseMoveEvent(QMouseEvent * event)
{
	if (event->buttons() && Qt::LeftButton)
	{
		setCurrentFrame(positionToFrame(event->pos().x()));
	}
}

// get frame from x position
int TimeLineRule::positionToFrame(double x)
{
	return round(x * m_nFrameNum / width());
}

// get x position from frame
double TimeLineRule::frameToPosition(int frame)
{
	return frame * width() / m_nFrameNum;
}
