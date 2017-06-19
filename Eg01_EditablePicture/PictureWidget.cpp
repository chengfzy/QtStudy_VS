#include "PictureWidget.h"

PictureWidget::PictureWidget(QWidget *parent)
	: QWidget(parent)
	, m_logo(QPixmap()), m_cursorPosition(CursorPosition::Undefined)
	, m_bMousePressed(false)
	, m_borderColor(Qt::darkGray)
{
	setAutoFillBackground(true);
	setMouseTracking(true);
}

PictureWidget::~PictureWidget()
{
}

//set image
void PictureWidget::SetImages(const QPixmap & image)
{
	setFixedSize(image.size());
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(image));
	setPalette(palette);
}

//set logo
void PictureWidget::SetLogo(const QPixmap & logo)
{
	m_logo = logo;
	m_logoRatio.setWidth(static_cast<double>(logo.width()) / logo.height());
	m_logoRatio.setHeight(static_cast<double>(logo.height()) / logo.width());
	m_logoRect = QRect((rect().width() - logo.width()) / 2, (rect().height() - logo.height()) / 2, logo.width(), logo.height());
	update();
}

void PictureWidget::paintEvent(QPaintEvent * event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);

	//draw picture
	painter.drawPixmap(m_logoRect.x(), m_logoRect.y(), m_logo.scaled(m_logoRect.size().toSize()));

	//draw border rect
	QPen dashPen(m_borderColor);
	dashPen.setStyle(Qt::DashLine);
	painter.setPen(dashPen);
	painter.setBrush(QBrush(Qt::transparent));
	painter.drawRect(m_logoRect);

	//draw control points in border
	painter.setPen(m_borderColor);
	painter.setBrush(QBrush(m_borderColor));
	int leftX = m_logoRect.left() - 2;
	int centerX = m_logoRect.center().x() - 3;
	int rightX = m_logoRect.right() - 2;
	int topY = m_logoRect.top() - 2;
	int centerY = m_logoRect.center().y() - 3;
	int bottomY = m_logoRect.bottom() - 2;
	const QSize pointSize(5, 5);		//rect size
	QVector<QRect> points;
	points << QRect(QPoint(leftX, topY), pointSize)
		<< QRect(QPoint(leftX, centerY), pointSize)
		<< QRect(QPoint(leftX, bottomY), pointSize)
		<< QRect(QPoint(centerX, topY), pointSize)
		<< QRect(QPoint(centerX, bottomY), pointSize)
		<< QRect(QPoint(rightX, topY), pointSize)
		<< QRect(QPoint(rightX, centerY), pointSize)
		<< QRect(QPoint(rightX, bottomY), pointSize);
	painter.drawRects(points);

	//draw dash line
	painter.setPen(dashPen);
	painter.drawLine(QPoint(m_logoRect.center().x(), m_logoRect.top()), QPoint(m_logoRect.center().x(), m_logoRect.bottom()));
	painter.drawLine(QPoint(m_logoRect.left(), m_logoRect.center().y()), QPoint(m_logoRect.right(), m_logoRect.center().y()));

	painter.end();
}

void PictureWidget::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bMousePressed = true;
		m_startMousePos = event->pos();
		m_lastLogoRect = m_logoRect;
	}
	updateCursor(event->pos());
}

void PictureWidget::mouseMoveEvent(QMouseEvent * event)
{
	QPointF mousePos = event->pos();

	if (!m_bMousePressed)
	{
		m_cursorPosition = getCursorPosition(mousePos);
		updateCursor(mousePos);
	}
	else if (m_cursorPosition != CursorPosition::Undefined)
	{
		QPointF mouseDelta;
		mouseDelta.setX(mousePos.x() - m_startMousePos.x());
		mouseDelta.setY(mousePos.y() - m_startMousePos.y());

		if (m_cursorPosition == CursorPosition::Middle)
		{
			//move
			QPointF moveDelta = m_lastLogoRect.topLeft() + mouseDelta;
			//bound limit
			if (moveDelta.x() < 0)
				moveDelta.setX(0);
			if (moveDelta.y() < 0)
				moveDelta.setY(0);
			if (moveDelta.x() + m_logoRect.width() > rect().width())
				moveDelta.setX(rect().width() - m_logoRect.width());
			if (moveDelta.y() + m_logoRect.height() > rect().height())
				moveDelta.setY(rect().height() - m_logoRect.height());

			m_logoRect.moveTo(moveDelta);
		}
		else
		{
			//Resize
			QRectF newGeometry = calculateImageGeometry(m_lastLogoRect, mouseDelta);
			if (!newGeometry.isNull())
				m_logoRect = newGeometry;
		}
		update();
	}
}

void PictureWidget::mouseReleaseEvent(QMouseEvent * event)
{
	m_bMousePressed = false;
	updateCursor(event->pos());
}

bool PictureWidget::isPointNearSide(int sideCoord, int pointCoord)
{
	static const int indent{ 10 };
	return (sideCoord - indent) < pointCoord && pointCoord < sideCoord + indent;
}

CursorPosition PictureWidget::getCursorPosition(const QPointF & mousePosition)
{
	CursorPosition cursorPosition = CursorPosition::Undefined;

	if (m_logoRect.contains(mousePosition))
	{
		if (isPointNearSide(m_logoRect.top(), mousePosition.y()))
		{
			if (isPointNearSide(m_logoRect.left(), mousePosition.x()))
				cursorPosition = CursorPosition::TopLeft;
			else if (isPointNearSide(m_logoRect.right(), mousePosition.x()))
				cursorPosition = CursorPosition::TopRight;
			else
				cursorPosition = CursorPosition::Top;
		}
		else if(isPointNearSide(m_logoRect.bottom(), mousePosition.y()))
		{
			if (isPointNearSide(m_logoRect.left(), mousePosition.x()))
				cursorPosition = CursorPosition::BottomLeft;
			else if (isPointNearSide(m_logoRect.right(), mousePosition.x()))
				cursorPosition = CursorPosition::BottomRight;
			else
				cursorPosition = CursorPosition::Bottom;
		}
		else if (isPointNearSide(m_logoRect.left(), mousePosition.x()))
		{
			cursorPosition = CursorPosition::Left;
		}
		else if (isPointNearSide(m_logoRect.right(), mousePosition.x()))
		{
			cursorPosition = CursorPosition::Right;
		}
		else
			cursorPosition = CursorPosition::Middle;
	}

	return cursorPosition;
}

//update mouse cursor
void PictureWidget::updateCursor(const QPointF & mousePosition)
{
	QCursor cursor;

	switch (getCursorPosition(mousePosition))
	{
	case CursorPosition::TopLeft:
	case CursorPosition::BottomRight:
		cursor = QCursor(Qt::SizeFDiagCursor);
		break;
	case CursorPosition::TopRight:
	case CursorPosition::BottomLeft:
		cursor = QCursor(Qt::SizeBDiagCursor);
		break;
	case CursorPosition::Top:
	case CursorPosition::Bottom:
		cursor = QCursor(Qt::SizeVerCursor);
		break;
	case CursorPosition::Left:
	case CursorPosition::Right:
		cursor = QCursor(Qt::SizeHorCursor);
		break;
	case CursorPosition::Middle:
		cursor = m_bMousePressed ? QCursor(Qt::ClosedHandCursor) : QCursor(Qt::OpenHandCursor);
		break;
	case CursorPosition::Undefined:
	default:
		cursor = QCursor(Qt::ArrowCursor);
		break;
	}

	setCursor(cursor);
}

QRectF PictureWidget::calculateImageGeometry(const QRectF & sourceGeometry, const QPointF & mouseDelta)
{
	QRectF resultGeometry = sourceGeometry;

	switch (m_cursorPosition)
	{
	case CursorPosition::Top:
		resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
		resultGeometry.setRight(sourceGeometry.right() - mouseDelta.y() * m_logoRatio.width());
		break;
	case CursorPosition::Bottom:
		resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
		resultGeometry.setRight(sourceGeometry.right() + mouseDelta.y() * m_logoRatio.width());
		break;
	case CursorPosition::Left:
		resultGeometry.setTop(sourceGeometry.top() + mouseDelta.x() * m_logoRatio.height());
		resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		break;
	case CursorPosition::Right:
		resultGeometry.setTop(sourceGeometry.top() - mouseDelta.x() * m_logoRatio.height());
		resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		break;
	case CursorPosition::TopLeft:
		if (mouseDelta.x() * m_logoRatio.height() < mouseDelta.y())
		{
			resultGeometry.setTop(sourceGeometry.top() + mouseDelta.x() * m_logoRatio.height());
			resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		}
		else
		{
			resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
			resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.y() * m_logoRatio.width());
		}
		break;
	case CursorPosition::TopRight:
		if ((mouseDelta.x() * m_logoRatio.height() * -1) < mouseDelta.y())
		{
			resultGeometry.setTop(sourceGeometry.top() - mouseDelta.x() * m_logoRatio.height());
			resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		}
		else
		{
			resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
			resultGeometry.setRight(sourceGeometry.right() - mouseDelta.y() * m_logoRatio.width());
		}
		break;
	case CursorPosition::BottomLeft:
		if (mouseDelta.x() * m_logoRatio.height() < mouseDelta.y() * -1)
		{
			resultGeometry.setBottom(sourceGeometry.bottom() - mouseDelta.x() * m_logoRatio.height());
			resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		}
		else
		{
			resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
			resultGeometry.setLeft(sourceGeometry.left() - mouseDelta.y() * m_logoRatio.width());
		}
		break;
	case CursorPosition::BottomRight:
		if ((mouseDelta.x() * m_logoRatio.height()) > mouseDelta.y())
		{
			resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.x() * m_logoRatio.height());
			resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		}
		else
		{
			resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
			resultGeometry.setRight(sourceGeometry.right() + mouseDelta.y() * m_logoRatio.width());
		}
		break;
	default:
		break;
	}

	if ((resultGeometry.left() >= resultGeometry.right()) || (resultGeometry.top() >= resultGeometry.bottom()))
	{
		resultGeometry = QRect();
	}

	return resultGeometry;
}
