#include "ImageCropper.h"

namespace
{
	const QRect INIT_CROPPING_RECT = QRect();
	const QSizeF INIT_PROPORTION = QSizeF(1.0, 1.0);
	static const QSize WIDGET_MINIMUM_SIZE(300, 300);
}


ImageCropper::ImageCropper(QWidget *parent)
	: QWidget(parent)
	, m_image(QPixmap()),
	m_croppingRect(INIT_CROPPING_RECT),
	m_lastStaticCroppingRect(QRect()),
	m_cursorPosition(CursorPositionUndefined),
	m_bMousePressed(false),
	m_bProportionFixed(false),
	m_startMousePos(QPoint()),
	m_proportion(INIT_PROPORTION),
	m_deltas(INIT_PROPORTION),
	m_backgroundColor(Qt::black),
	m_croppingRectBorderColor(Qt::white)
{
	setMinimumSize(WIDGET_MINIMUM_SIZE);
	setMouseTracking(true);
}

ImageCropper::~ImageCropper()
{
}

void ImageCropper::setImage(const QPixmap& image)
{
	m_image = image;
	update();
}

void ImageCropper::setBackgroundColor(const QColor& backgroundColor)
{
	m_backgroundColor = backgroundColor;
	update();
}

void ImageCropper::setCroppingRectBorderColor(const QColor& borderColor)
{
	m_croppingRectBorderColor = borderColor;
	update();
}

void ImageCropper::setProportion(const QSizeF& proportion)
{
	// §±§â§à§á§à§â§è§Ú§Ú §ç§â§Ñ§ß§ñ§ä§ã§ñ §Ó §Ü§à§ï§æ§æ§Ú§è§Ú§Ö§ß§ä§Ñ§ç §á§â§Ú§â§Ñ§ë§Ö§ß§Ú§ñ §ã§ä§à§â§à§ß
	// §´§Ñ§Ü§Ú§Þ §à§Ò§â§Ñ§Ù§à§Þ, §á§â§Ú §Ú§Ù§Þ§Ö§ß§Ö§ß§Ú§Ú §â§Ñ§Ù§Þ§Ö§â§Ñ §à§Ò§Ý§Ñ§ã§ä§Ú §Ó§í§Õ§Ö§Ý§Ö§ß§Ú§ñ,
	// §â§Ñ§Ù§Þ§Ö§â§í §ã§ä§à§â§à§ß §Ú§Ù§Þ§Ö§ß§ñ§ð§ä§ã§ñ §ß§Ñ §â§Ñ§Ù§Þ§Ö§â §Ù§Ñ§Ó§Ú§ã§ñ§ë§Ú§Û §à§ä
	// §Ü§à§ï§æ§æ§Ú§è§Ú§Ö§ß§ä§à§Ó §á§â§Ú§â§Ñ§ë§Ö§ß§Ú§ñ.

	// §³§à§ç§â§Ñ§ß§Ú§Þ §á§â§à§á§à§â§è§Ú§à§ß§Ñ§Ý§î§ß§å§ð §Ù§Ñ§Ó§Ú§ã§Ú§Þ§à§ã§ä§î §à§Ò§Ý§Ñ§ã§ä§Ú §Ó§í§Õ§Ö§Ý§Ö§ß§Ú§ñ §Ó §Ü§à§ï§æ§æ§Ú§è§Ú§Ö§ß§ä§Ñ§ç §á§â§Ú§â§Ñ§ë§Ö§ß§Ú§ñ §ã§ä§à§â§à§ß
	if (m_proportion != proportion)
	{
		m_proportion = proportion;
		// ... §â§Ñ§ã§é§Ú§ä§Ñ§Ö§Þ §Ü§à§ï§æ§æ§Ú§è§Ú§Ö§ß§ä§í
		float heightDelta = (float)proportion.height() / proportion.width();
		float widthDelta = (float)proportion.width() / proportion.height();
		// ... §ã§à§ç§â§Ñ§ß§Ú§Þ §Ü§à§ï§æ§æ§Ú§è§Ú§Ö§ß§ä§í
		m_deltas.setHeight(heightDelta);
		m_deltas.setWidth(widthDelta);
	}

	// §°§Ò§ß§à§Ó§Ú§Þ §á§â§à§á§à§â§è§Ú§Ú §à§Ò§Ý§Ñ§ã§ä§Ú §Ó§í§Õ§Ö§Ý§Ö§ß§Ú§ñ
	if (m_bProportionFixed)
	{
		float croppintRectSideRelation = (float)m_croppingRect.width() / m_croppingRect.height();
		float proportionSideRelation = (float)m_proportion.width() / m_proportion.height();
		// §¦§ã§Ý§Ú §à§Ò§Ý§Ñ§ã§ä§î §Ó§í§Õ§Ö§Ý§Ö§ß§Ú§ñ §ß§Ö §ã§à§à§ä§Ó§Ö§ä§ã§ä§Ó§å§Ö§ä §ß§Ö§à§Ò§ç§à§Õ§Ú§Þ§í§Þ §á§â§à§á§à§â§è§Ú§ñ§Þ §à§Ò§ß§à§Ó§Ú§Þ §Ö§×
		if (croppintRectSideRelation != proportionSideRelation)
		{
			bool widthShotrerThenHeight = m_croppingRect.width() < m_croppingRect.height();
			// ... §å§ã§ä§Ñ§ß§à§Ó§Ú§Þ §â§Ñ§Ù§Þ§Ö§â §ä§à§Û §ã§ä§à§â§à§ß§í, §é§ä§à §Õ§Ý§Ú§ß§ß§Ö§Ö
			if (widthShotrerThenHeight)
			{
				m_croppingRect.setHeight(m_croppingRect.width() * m_deltas.height());
			}
			else
			{
				m_croppingRect.setWidth(m_croppingRect.height() * m_deltas.width());
			}
			// ... §á§Ö§â§Ö§â§Ú§ã§å§Ö§Þ §Ó§Ú§Õ§Ø§Ö§ä
			update();
		}
	}
}

void ImageCropper::setProportionFixed(const bool isFixed)
{
	if (m_bProportionFixed != isFixed)
	{
		m_bProportionFixed = isFixed;
		setProportion(m_proportion);
	}
}


const QPixmap ImageCropper::cropImage()
{
	// §±§à§Ý§å§é§Ú§Þ §â§Ñ§Ù§Þ§Ö§â §à§ä§à§Ò§â§Ñ§Ø§Ñ§Ö§Þ§à§Ô§à §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§ñ
	QSize scaledImageSize = m_image.scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation).size();
	// §°§á§â§Ö§Õ§Ö§Ý§Ú§Þ §â§Ñ§ã§ã§ä§à§ñ§ß§Ú§Ö §à§ä §Ý§Ö§Ó§à§Ô§à §Ú §Ó§Ö§â§ç§ß§Ö§Ô§à §Ü§â§Ñ§×§Ó
	float leftDelta = 0;
	float topDelta = 0;
	const float HALF_COUNT = 2;
	if (this->size().height() == scaledImageSize.height())
	{
		leftDelta = (this->width() - scaledImageSize.width()) / HALF_COUNT;
	}
	else
	{
		topDelta = (this->height() - scaledImageSize.height()) / HALF_COUNT;
	}
	// §°§á§â§Ö§Õ§Ö§Ý§Ú§Þ §á§â§à§á§à§â§è§Ú§ð §à§Ò§Ý§Ñ§ã§ä§Ú §à§Ò§â§Ö§Ù§Ü§Ú §á§à §à§ä§ß§à§ê§Ö§ß§Ú§ð §Ü §Ú§ã§ç§à§Õ§ß§à§Þ§å §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§ð
	float xScale = (float)m_image.width() / scaledImageSize.width();
	float yScale = (float)m_image.height() / scaledImageSize.height();
	// §²§Ñ§ã§é§Ú§ä§Ñ§Ö§Þ §à§Ò§Ý§Ñ§ã§ä§î §à§Ò§â§Ö§Ù§Ü§Ú §ã §å§é§×§ä§à§Þ §Ü§à§â§â§Ö§Ü§è§Ú§Ú §â§Ñ§Ù§Þ§Ö§â§à§Ó §Ú§ã§ç§à§Õ§ß§à§Ô§à §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§ñ
	QRectF realSizeRect(QPointF(m_croppingRect.left() - leftDelta, m_croppingRect.top() - topDelta), m_croppingRect.size());
	// ... §Ü§à§â§â§Ö§Ü§ä§Ú§â§å§Ö§Þ §Ý§Ö§Ó§í§Û §Ú §Ó§Ö§â§ç§ß§Ú§Û §Ü§â§Ñ§ñ
	realSizeRect.setLeft((m_croppingRect.left() - leftDelta) * xScale);
	realSizeRect.setTop((m_croppingRect.top() - topDelta) * yScale);
	// ... §Ü§à§â§â§Ö§Ü§ä§Ú§â§å§Ö§Þ §â§Ñ§Ù§Þ§Ö§â
	realSizeRect.setWidth(m_croppingRect.width() * xScale);
	realSizeRect.setHeight(m_croppingRect.height() * yScale);
	// §±§à§Ý§å§é§Ñ§Ö§Þ §à§Ò§â§Ö§Ù§Ñ§ß§ß§à§Ö §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö
	return m_image.copy(realSizeRect.toRect());
}


void ImageCropper::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);
	
	//draw picture
	{
		// ... §á§à§Õ§Ô§à§ß§Ú§Þ §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö §Õ§Ý§ñ §à§ä§à§Ò§â§Ñ§Ø§Ö§ß§Ú§ñ §á§à §â§Ñ§Ù§Þ§Ö§â§å §Ó§Ú§Õ§Ø§Ö§ä§Ñ
		QPixmap scaledImage = m_image.scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
		// ... §Ù§Ñ§Ý§Ú§Ó§Ñ§Ö§Þ §æ§à§ß
		painter.fillRect(this->rect(), m_backgroundColor);
		// ... §â§Ú§ã§å§Ö§Þ §Ú§Ù§à§Ò§â§Ñ§Ø§Ö§ß§Ú§Ö §á§à §è§Ö§ß§ä§â§å §Ó§Ú§Õ§Ø§Ö§ä§Ñ
		if (this->size().height() == scaledImage.height())
		{
			painter.drawPixmap((this->width() - scaledImage.width()) / 2, 0, scaledImage);
		}
		else
		{
			painter.drawPixmap(0, (this->height() - scaledImage.height()) / 2, scaledImage);
		}
	}
	
	//draw crop rect
	{
		//crop rect size
		if (m_croppingRect.isNull())
		{
			const int width = WIDGET_MINIMUM_SIZE.width() / 2;
			const int height = WIDGET_MINIMUM_SIZE.height() / 2;
			m_croppingRect.setSize(QSize(width, height));
			float x = (this->width() - m_croppingRect.width()) / 2;
			float y = (this->height() - m_croppingRect.height()) / 2;
			m_croppingRect.moveTo(x, y);
		}

		//draw crop rect
		QPainterPath p;
		p.addRect(m_croppingRect);
		p.addRect(this->rect());
		painter.setBrush(QBrush(QColor(0, 0, 0, 120)));
		painter.setPen(Qt::transparent);
		painter.drawPath(p);
		//set color
		painter.setPen(m_croppingRectBorderColor);
		painter.setBrush(QBrush(Qt::transparent));
		painter.drawRect(m_croppingRect);
		
		//control points in edge and center
		{
			painter.setBrush(QBrush(m_croppingRectBorderColor));
			// §£§ã§á§à§Þ§à§Ô§Ñ§ä§Ö§Ý§î§ß§í§Ö X §Ü§à§à§â§Õ§Ú§ß§Ñ§ä§í
			int leftXCoord = m_croppingRect.left() - 2;
			int centerXCoord = m_croppingRect.center().x() - 3;
			int rightXCoord = m_croppingRect.right() - 2;
			// §£§ã§á§à§Þ§à§Ô§Ñ§ä§Ö§Ý§î§ß§í§Ö Y §Ü§à§à§â§Õ§Ú§ß§Ñ§ä§í
			int topYCoord = m_croppingRect.top() - 2;
			int middleYCoord = m_croppingRect.center().y() - 3;
			int bottomYCoord = m_croppingRect.bottom() - 2;
			//
			const QSize pointSize(6, 6);
			//
			QVector<QRect> points;
			points << QRect(QPoint(leftXCoord, topYCoord), pointSize)	// left point
				<< QRect(QPoint(leftXCoord, middleYCoord), pointSize)
				<< QRect(QPoint(leftXCoord, bottomYCoord), pointSize)
				<< QRect(QPoint(centerXCoord, topYCoord), pointSize)	// center point
				<< QRect(QPoint(centerXCoord, middleYCoord), pointSize)
				<< QRect(QPoint(centerXCoord, bottomYCoord), pointSize)
				<< QRect(QPoint(rightXCoord, topYCoord), pointSize)		// right point
				<< QRect(QPoint(rightXCoord, middleYCoord), pointSize)
				<< QRect(QPoint(rightXCoord, bottomYCoord), pointSize);
			//
			painter.drawRects(points);
		}

		//dash line
		{
			QPen dashPen(m_croppingRectBorderColor);
			dashPen.setStyle(Qt::DashLine);
			painter.setPen(dashPen);
			//vectical line
			painter.drawLine(QPoint(m_croppingRect.center().x(), m_croppingRect.top()),
				QPoint(m_croppingRect.center().x(), m_croppingRect.bottom()));
			//horizontal line
			painter.drawLine(QPoint(m_croppingRect.left(), m_croppingRect.center().y()),
				QPoint(m_croppingRect.right(), m_croppingRect.center().y()));
		}
	}

	painter.end();
}


void ImageCropper::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bMousePressed = true;
		m_startMousePos = event->pos();
		m_lastStaticCroppingRect = m_croppingRect;
	}
	//
	updateCursorIcon(event->pos());
}

void ImageCropper::mouseMoveEvent(QMouseEvent* event)
{
	QPointF mousePos = event->pos(); // §à§ä§ß§à§ã§Ú§ä§Ö§Ý§î§ß§à §ã§Ö§Ò§ñ (§Ó§Ú§Õ§Ø§Ö§ä§Ñ)
									  //
	if (!m_bMousePressed)
	{
		// §°§Ò§â§Ñ§Ò§à§ä§Ü§Ñ §à§Ò§í§é§ß§à§Ô§à §ã§à§ã§ä§à§ñ§ß§Ú§ñ, §ä.§Ö. §ß§Ö §Ú§Ù§Þ§Ö§ß§ñ§Ö§ä§ã§ñ §â§Ñ§Ù§Þ§Ö§â
		// §à§Ò§Ý§Ñ§ã§ä§Ú §à§Ò§â§Ö§Ù§Ü§Ú, §Ú §à§ß§Ñ §ß§Ö §á§Ö§â§Ö§Þ§Ö§ë§Ñ§Ö§ä§ã§ñ §á§à §Ó§Ú§Õ§Ø§Ö§ä§å
		m_cursorPosition = getcursorPosition(m_croppingRect, mousePos);
		updateCursorIcon(mousePos);
	}
	else if (m_cursorPosition != CursorPositionUndefined)
	{
		// §°§Ò§â§Ñ§Ò§à§ä§Ü§Ñ §Õ§Ö§Û§ã§ä§Ó§Ú§Û §ß§Ñ§Õ §à§Ò§Ý§Ñ§ã§ä§î§ð §à§Ò§â§Ö§Ù§Ü§Ú
		// ... §à§á§â§Ö§Õ§Ö§Ý§Ú§Þ §ã§Þ§Ö§ë§Ö§ß§Ú§Ö §Ü§å§â§ã§à§â§Ñ §Þ§í§ê§Ü§Ú
		QPointF mouseDelta;
		mouseDelta.setX(mousePos.x() - m_startMousePos.x());
		mouseDelta.setY(mousePos.y() - m_startMousePos.y());
		//
		if (m_cursorPosition != CursorPositionMiddle)
		{
			// ... §Ú§Ù§Þ§Ö§ß§ñ§Ö§Þ §â§Ñ§Ù§Þ§Ö§â §à§Ò§Ý§Ñ§ã§ä§Ú §à§Ò§â§Ö§Ù§Ü§Ú
			QRectF newGeometry = calculateGeometry(m_lastStaticCroppingRect, m_cursorPosition, mouseDelta);
			// ... §á§à§Ý§î§Ù§à§Ó§Ñ§ä§Ö§Ý§î §á§í§ä§Ñ§Ö§ä§ã§ñ §Ó§í§Ó§Ö§â§ß§å§ä§î §à§Ò§Ý§Ñ§ã§ä§î §à§Ò§â§Ö§Ù§Ü§Ú §ß§Ñ§Ú§Ù§ß§Ñ§ß§Ü§å
			if (!newGeometry.isNull())
				m_croppingRect = newGeometry;
		}
		else
		{
			// ... §á§Ö§â§Ö§Þ§Ö§ë§Ñ§Ö§Þ §à§Ò§Ý§Ñ§ã§ä§î §à§Ò§â§Ö§Ù§Ü§Ú
			m_croppingRect.moveTo(m_lastStaticCroppingRect.topLeft() + mouseDelta);
		}
		// §±§Ö§â§Ö§â§Ú§ã§å§Ö§Þ §Ó§Ú§Õ§Ø§Ö§ä
		update();
	}
}

void ImageCropper::mouseReleaseEvent(QMouseEvent* event)
{
	m_bMousePressed = false;
	updateCursorIcon(event->pos());
}


CursorPosition ImageCropper::getcursorPosition(const QRectF& cropRect, const QPointF& mousePosition)
{
	CursorPosition cursorPosition = CursorPositionUndefined;

	if (cropRect.contains(mousePosition))
	{
		if (isPointNearSide(cropRect.top(), mousePosition.y()) && isPointNearSide(cropRect.left(), mousePosition.x()))
		{
			cursorPosition = CursorPositionTopLeft;
		}
		else if (isPointNearSide(cropRect.bottom(), mousePosition.y()) && isPointNearSide(cropRect.left(), mousePosition.x()))
		{
			cursorPosition = CursorPositionBottomLeft;
		}
		else if (isPointNearSide(cropRect.top(), mousePosition.y()) && isPointNearSide(cropRect.right(), mousePosition.x()))
		{
			cursorPosition = CursorPositionTopRight;
		}
		else if (isPointNearSide(cropRect.bottom(), mousePosition.y()) && isPointNearSide(cropRect.right(), mousePosition.x()))
		{
			cursorPosition = CursorPositionBottomRight;
		}
		else if (isPointNearSide(cropRect.left(), mousePosition.x()))
		{
			cursorPosition = CursorPositionLeft;
		}
		else if (isPointNearSide(cropRect.right(), mousePosition.x()))
		{
			cursorPosition = CursorPositionRight;
		}
		else if (isPointNearSide(cropRect.top(), mousePosition.y()))
		{
			cursorPosition = CursorPositionTop;
		}
		else if (isPointNearSide(cropRect.bottom(), mousePosition.y()))
		{
			cursorPosition = CursorPositionBottom;
		}
		else
		{
			cursorPosition = CursorPositionMiddle;
		}
	}
	return cursorPosition;
}

void ImageCropper::updateCursorIcon(const QPointF& mousePosition)
{
	QCursor cursorIcon;

	switch (getcursorPosition(m_croppingRect, mousePosition))
	{
	case CursorPositionTopRight:
	case CursorPositionBottomLeft:
		cursorIcon = QCursor(Qt::SizeBDiagCursor);
		break;
	case CursorPositionTopLeft:
	case CursorPositionBottomRight:
		cursorIcon = QCursor(Qt::SizeFDiagCursor);
		break;
	case CursorPositionTop:
	case CursorPositionBottom:
		cursorIcon = QCursor(Qt::SizeVerCursor);
		break;
	case CursorPositionLeft:
	case CursorPositionRight:
		cursorIcon = QCursor(Qt::SizeHorCursor);
		break;
	case CursorPositionMiddle:
		cursorIcon = m_bMousePressed ? QCursor(Qt::ClosedHandCursor) : QCursor(Qt::OpenHandCursor);
		break;
	case CursorPositionUndefined:
	default:
		cursorIcon = QCursor(Qt::ArrowCursor);
		break;
	}

	this->setCursor(cursorIcon);
}

const QRectF ImageCropper::calculateGeometry(const QRectF& sourceGeometry, const CursorPosition cursorPosition, const QPointF& mouseDelta)
{
	QRectF resultGeometry;

	if (m_bProportionFixed)
	{
		resultGeometry = calculateGeometryWithFixedProportions(sourceGeometry, cursorPosition, mouseDelta, m_deltas);
	}
	else
	{
		resultGeometry = calculateGeometryWithCustomProportions(sourceGeometry, cursorPosition, mouseDelta);
	}
	// §¦§ã§Ý§Ú §á§à§Ý§î§Ù§à§Ó§Ñ§ä§Ö§Ý§î §á§í§ä§Ñ§Ö§ä§ã§ñ §Ó§í§Ó§Ö§â§ß§å§ä§î §à§Ò§Ý§Ñ§ã§ä§î §à§Ò§â§Ö§Ù§Ü§Ú §ß§Ñ§Ú§Ù§ß§Ñ§ß§Ü§å,
	// §Ó§à§Ù§Ó§â§Ñ§ë§Ñ§Ö§Þ null-§á§â§ñ§Þ§à§å§Ô§à§Ý§î§ß§Ú§Ü
	if ((resultGeometry.left() >= resultGeometry.right()) || (resultGeometry.top() >= resultGeometry.bottom()))
	{
		resultGeometry = QRect();
	}

	return resultGeometry;
}

const QRectF ImageCropper::calculateGeometryWithCustomProportions(const QRectF& sourceGeometry,
	const CursorPosition cursorPosition, const QPointF& mouseDelta)
{
	QRectF resultGeometry = sourceGeometry;

	switch (cursorPosition)
	{
	case CursorPositionTopLeft:
		resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
		break;
	case CursorPositionTopRight:
		resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
		resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		break;
	case CursorPositionBottomLeft:
		resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
		resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		break;
	case CursorPositionBottomRight:
		resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
		resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		break;
	case CursorPositionTop:
		resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
		break;
	case CursorPositionBottom:
		resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
		break;
	case CursorPositionLeft:
		resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		break;
	case CursorPositionRight:
		resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		break;
	default:
		break;
	}

	return resultGeometry;
}

const QRectF ImageCropper::calculateGeometryWithFixedProportions(const QRectF& sourceGeometry,
	const CursorPosition cursorPosition, const QPointF& mouseDelta, const QSizeF& deltas)
{
	QRectF resultGeometry = sourceGeometry;

	switch (cursorPosition)
	{
	case CursorPositionLeft:
		resultGeometry.setTop(sourceGeometry.top() + mouseDelta.x() * deltas.height());
		resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		break;
	case CursorPositionRight:
		resultGeometry.setTop(sourceGeometry.top() - mouseDelta.x() * deltas.height());
		resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		break;
	case CursorPositionTop:
		resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
		resultGeometry.setRight(sourceGeometry.right() - mouseDelta.y() * deltas.width());
		break;
	case CursorPositionBottom:
		resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
		resultGeometry.setRight(sourceGeometry.right() + mouseDelta.y() * deltas.width());
		break;
	case CursorPositionTopLeft:
		if (mouseDelta.x() * deltas.height() < mouseDelta.y()) 
		{
			resultGeometry.setTop(sourceGeometry.top() + mouseDelta.x() * deltas.height());
			resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		}
		else 
		{
			resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
			resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.y() * deltas.width());
		}
		break;
	case CursorPositionTopRight:
		if ((mouseDelta.x() * deltas.height() * -1) < mouseDelta.y()) 
		{
			resultGeometry.setTop(sourceGeometry.top() - mouseDelta.x() * deltas.height());
			resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		}
		else 
		{
			resultGeometry.setTop(sourceGeometry.top() + mouseDelta.y());
			resultGeometry.setRight(sourceGeometry.right() - mouseDelta.y() * deltas.width());
		}
		break;
	case CursorPositionBottomLeft:
		if (mouseDelta.x() * deltas.height() < mouseDelta.y() * -1) 
		{
			resultGeometry.setBottom(sourceGeometry.bottom() - mouseDelta.x() * deltas.height());
			resultGeometry.setLeft(sourceGeometry.left() + mouseDelta.x());
		}
		else
		{
			resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
			resultGeometry.setLeft(sourceGeometry.left() - mouseDelta.y() * deltas.width());
		}
		break;
	case CursorPositionBottomRight:
		if ((mouseDelta.x() * deltas.height()) > mouseDelta.y()) 
		{
			resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.x() * deltas.height());
			resultGeometry.setRight(sourceGeometry.right() + mouseDelta.x());
		}
		else
		{
			resultGeometry.setBottom(sourceGeometry.bottom() + mouseDelta.y());
			resultGeometry.setRight(sourceGeometry.right() + mouseDelta.y() * deltas.width());
		}
		break;
	default:
		break;
	}

	return resultGeometry;
}

//is the point next to the coordinate of the side
bool ImageCropper::isPointNearSide(const int sideCoordinate, const int pointCoordinate)
{
	static const int indent = 10;
	return (sideCoordinate - indent) < pointCoordinate && pointCoordinate < (sideCoordinate + indent);
}
