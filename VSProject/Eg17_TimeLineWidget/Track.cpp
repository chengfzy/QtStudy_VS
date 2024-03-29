#include "Track.h"
#include <QtWidgets>

static const int g_nMouseAdjustThresh = 5;

Track::Track(QTime duration, int frameNum, QWidget *parent)
	: TimeLineRule(duration, frameNum, parent)
	, m_nStartFrame(0), m_nEndFrame(0)
	, m_bSelected(false), m_bAdjustStart(false), m_bAdjustEnd(false), m_bMouseDrag(false)
{
	setFixedHeight(100);
	setMouseTracking(true);
}

Track::~Track()
{
}

int Track::startFrame() const
{
	return m_nStartFrame;
}

int Track::endFrame() const
{
	return m_nEndFrame;
}

QString Track::title() const
{
	return m_szTitle;
}

bool Track::isSelected() const
{
	return m_bSelected;
}

void Track::setStartFrame(int frame)
{
	if (0 <= frame && frame <= m_nEndFrame)
	{
		m_nStartFrame = frame;
		emit startFrameChanged(m_nStartFrame);
	}
}

void Track::setEndFrame(int frame)
{
	if (m_nStartFrame <= frame && frame < m_nFrameNum)
	{
		m_nEndFrame = frame;
		emit endFrameChanged(m_nEndFrame);
	}
}

void Track::setTitle(const QString& title)
{
	m_szTitle = title;
}

void Track::setStartFrameImage(const QPixmap & image)
{
	m_startFrameThumb = image;
}

void Track::setEndFrameImage(const QPixmap & image)
{
	m_endFrameThumb = image;
}

void Track::setSelected(bool selected)
{
	m_bSelected = selected;
	if (m_bSelected)
		emit trackSelected();
	update();
}

// move region with delta frame
void Track::moveRegion(int deltaFrame)
{
	int startFrame = m_nStartFrame + deltaFrame;
	int endFrame = m_nEndFrame + deltaFrame;
	if (0 <= startFrame && endFrame < m_nFrameNum)
	{
		m_nStartFrame = startFrame;
		m_nEndFrame = endFrame;
		update();
	}
}

void Track::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	const int nHeight = height();
	const double dStartPix = frameToPosition(m_nStartFrame);
	const double dEndPix = frameToPosition(m_nEndFrame);

	//draw backgroud rect
	painter.save();
	painter.setPen(Qt::NoPen);
	if (m_bSelected)
		painter.setBrush(QColor(Qt::gray));
	else
		painter.setBrush(QColor(Qt::darkGray));
	painter.drawRect(this->rect());
	painter.restore();

	//draw label-track editor line
	painter.save();
	painter.setPen(QColor(Qt::white));
	painter.drawLine(m_nLabelWidth, 0, m_nLabelWidth, nHeight);
	painter.restore();

	//draw label text
	QString szLabel(tr("%1\r\n%2 Logos\r\n[%3 - %4]").arg(m_szTitle).arg(3).arg(m_nStartFrame).arg(m_nEndFrame));
	QRect labelRect(5, 0, m_nLabelWidth - 5, nHeight);
	painter.save();
	if (m_bSelected)
		painter.setPen(QColor(Qt::blue));
	else
		painter.setPen(QColor(Qt::black));
	painter.drawText(labelRect, Qt::AlignVCenter | Qt::AlignLeft, szLabel);
	painter.restore();

	//draw the track region
	painter.save();
	painter.setPen(QColor(Qt::darkBlue));
	QLinearGradient gradient(QPointF(0, 0), QPointF(0, nHeight));
	gradient.setColorAt(0, QColor(35, 165, 255));
	gradient.setColorAt(1, QColor(2, 49, 82));
	painter.setBrush(QBrush(gradient));
	painter.drawRect(QRectF(QPointF(dStartPix, 0), QPointF(dEndPix, nHeight)));
	painter.restore();

	//draw thumbnail in start frame
	const float fThumbHeight = nHeight * 0.7;
	QSize startThumbSize(m_startFrameThumb.width() * fThumbHeight / m_startFrameThumb.height(), fThumbHeight);
	painter.save();
	if (dEndPix - dStartPix >= startThumbSize.width())
	{
		painter.drawPixmap(QRect(QPoint(dStartPix, 0), startThumbSize), m_startFrameThumb);
	}
	else
	{
		int nStartThumbWidth = dEndPix - dStartPix;
		QPixmap drawImage = m_startFrameThumb.copy(QRect(0, 0, m_startFrameThumb.width() * nStartThumbWidth / startThumbSize.width(), m_startFrameThumb.height()));
		painter.drawPixmap(QRect(dStartPix, 0, nStartThumbWidth, startThumbSize.height()), drawImage);
	}
	painter.restore();

	//draw thumbnail in end frame
	QSize endThumbSize(m_endFrameThumb.width() * fThumbHeight / m_endFrameThumb.height(), fThumbHeight);
	if (dEndPix - dStartPix >= startThumbSize.width() + endThumbSize.width() + 5)
	{
		painter.save();
		painter.drawPixmap(QRect(QPoint(dEndPix - endThumbSize.width(), 0), endThumbSize), m_endFrameThumb);
		painter.restore();
	}

	//draw title text
	QStaticText titleStaticText(m_szTitle);
	QRectF titleRect(dStartPix, nHeight - 20, titleStaticText.size().width() + 2, titleStaticText.size().height());
	//draw rect
	painter.save();
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(255, 255, 255, 100)));
	painter.drawRect(titleRect);
	painter.restore();
	//draw text
	painter.save();
	painter.setPen(QColor(Qt::black));
	painter.drawStaticText(QPointF(titleRect.left() + 2, titleRect.top()), titleStaticText);
	painter.restore();

	//draw current frame linedraw current frame line
	painter.save();
	const double dCurrentFrameX = frameToPosition(m_nCurrentFrame);
	painter.setPen(QColor(Qt::white));
	painter.drawLine(dCurrentFrameX, 0, dCurrentFrameX, nHeight);
	painter.restore();
}

void Track::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (frameToPosition(m_nStartFrame) - g_nMouseAdjustThresh <= event->pos().x() && event->pos().x() <= frameToPosition(m_nStartFrame) + g_nMouseAdjustThresh
			&& (frameToPosition(m_nEndFrame) - frameToPosition(m_nStartFrame) >= g_nMouseAdjustThresh || frameToPosition(m_nStartFrame) - m_nLabelWidth >= g_nMouseAdjustThresh))
		{
			//adjust region left edge(start frame), the last check is ensure GUI workable when region is small and near widget border
			m_bAdjustStart = true;
			m_mousePos = event->pos();
			setCursor(Qt::SizeHorCursor);

			setSelected(true);
			event->accept();
			return;
		}
		else if (frameToPosition(m_nEndFrame) - g_nMouseAdjustThresh <= event->pos().x() && event->pos().x() <= frameToPosition(m_nEndFrame) + g_nMouseAdjustThresh)
		{
			//adjust region right edge(end frame)
			m_bAdjustEnd = true;
			m_mousePos = event->pos();
			setCursor(Qt::SizeHorCursor);

			setSelected(true);
			event->accept();
			return;
		}
		else if (frameToPosition(m_nStartFrame) <= event->pos().x() && event->pos().x() <= frameToPosition(m_nEndFrame))
		{
			//drag track region
			m_bMouseDrag = true;
			m_mousePos = event->pos();
			setCursor(Qt::OpenHandCursor);

			setSelected(true);
			event->accept();
			return;
		}
		else if (0 <= event->pos().x() && event->pos().x() <= m_nLabelWidth)
		{
			//select the label
			setSelected(true);
			event->accept();
			return;
		}
	}

	TimeLineRule::mousePressEvent(event);
}

void Track::mouseMoveEvent(QMouseEvent * event)
{
	if (event->buttons() && Qt::LeftButton)
	{
		if (m_bAdjustStart)
		{
			int deltaFrame = positionToFrame(event->pos().x()) - positionToFrame(m_mousePos.x());
			setStartFrame(m_nStartFrame + deltaFrame);
			m_mousePos = event->pos();
			update();
			event->accept();
			return;
		}
		else if (m_bAdjustEnd)
		{
			int deltaFrame = positionToFrame(event->pos().x()) - positionToFrame(m_mousePos.x());
			setEndFrame(m_nEndFrame + deltaFrame);
			m_mousePos = event->pos();
			update();
			event->accept();
			return;
		}
		else if (m_bMouseDrag)
		{
			//drag track region
			int deltaFrame = positionToFrame(event->pos().x()) - positionToFrame(m_mousePos.x());
			moveRegion(deltaFrame);
			m_mousePos = event->pos();
			event->accept();
			return;
		}
	}
	else if (frameToPosition(m_nStartFrame) - g_nMouseAdjustThresh <= event->pos().x() && event->pos().x() <= frameToPosition(m_nStartFrame) + g_nMouseAdjustThresh)
	{
		//near region left edge
		setCursor(Qt::SizeHorCursor);
	}
	else if (frameToPosition(m_nEndFrame) - g_nMouseAdjustThresh <= event->pos().x() && event->pos().x() <= frameToPosition(m_nEndFrame) + g_nMouseAdjustThresh)
	{
		//near region right edge
		setCursor(Qt::SizeHorCursor);
	}
	else
		setCursor(Qt::ArrowCursor);

	TimeLineRule::mouseMoveEvent(event);
}

void Track::mouseReleaseEvent(QMouseEvent * event)
{
	m_bAdjustStart = m_bAdjustEnd = m_bMouseDrag = false;	
	setCursor(Qt::ArrowCursor);
	TimeLineRule::mouseReleaseEvent(event);
}
