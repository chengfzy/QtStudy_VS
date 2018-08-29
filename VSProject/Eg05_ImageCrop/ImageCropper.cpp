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
	// ���������ڧ� ���ѧߧ���� �� �ܧ����ڧ�ڧ֧ߧ�ѧ� ���ڧ�ѧ�֧ߧڧ� �������
	// ���ѧܧڧ� ��ҧ�ѧ٧��, ���� �ڧ٧ާ֧ߧ֧ߧڧ� ��ѧ٧ާ֧�� ��ҧݧѧ��� �ӧ�է֧ݧ֧ߧڧ�,
	// ��ѧ٧ާ֧�� ������� �ڧ٧ާ֧ߧ����� �ߧ� ��ѧ٧ާ֧� �٧ѧӧڧ���ڧ� ���
	// �ܧ����ڧ�ڧ֧ߧ��� ���ڧ�ѧ�֧ߧڧ�.

	// ������ѧߧڧ� ��������ڧ�ߧѧݧ�ߧ�� �٧ѧӧڧ�ڧާ���� ��ҧݧѧ��� �ӧ�է֧ݧ֧ߧڧ� �� �ܧ����ڧ�ڧ֧ߧ�ѧ� ���ڧ�ѧ�֧ߧڧ� �������
	if (m_proportion != proportion)
	{
		m_proportion = proportion;
		// ... ��ѧ��ڧ�ѧ֧� �ܧ����ڧ�ڧ֧ߧ��
		float heightDelta = (float)proportion.height() / proportion.width();
		float widthDelta = (float)proportion.width() / proportion.height();
		// ... �����ѧߧڧ� �ܧ����ڧ�ڧ֧ߧ��
		m_deltas.setHeight(heightDelta);
		m_deltas.setWidth(widthDelta);
	}

	// ���ҧߧ�ӧڧ� ��������ڧ� ��ҧݧѧ��� �ӧ�է֧ݧ֧ߧڧ�
	if (m_bProportionFixed)
	{
		float croppintRectSideRelation = (float)m_croppingRect.width() / m_croppingRect.height();
		float proportionSideRelation = (float)m_proportion.width() / m_proportion.height();
		// ����ݧ� ��ҧݧѧ��� �ӧ�է֧ݧ֧ߧڧ� �ߧ� �����ӧ֧���ӧ�֧� �ߧ֧�ҧ��էڧާ�� ��������ڧ�� ��ҧߧ�ӧڧ� �֧�
		if (croppintRectSideRelation != proportionSideRelation)
		{
			bool widthShotrerThenHeight = m_croppingRect.width() < m_croppingRect.height();
			// ... ����ѧߧ�ӧڧ� ��ѧ٧ާ֧� ���� ������ߧ�, ���� �էݧڧߧߧ֧�
			if (widthShotrerThenHeight)
			{
				m_croppingRect.setHeight(m_croppingRect.width() * m_deltas.height());
			}
			else
			{
				m_croppingRect.setWidth(m_croppingRect.height() * m_deltas.width());
			}
			// ... ��֧�֧�ڧ��֧� �ӧڧէا֧�
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
	// ����ݧ��ڧ� ��ѧ٧ާ֧� ����ҧ�ѧاѧ֧ާ�ԧ� �ڧ٧�ҧ�ѧا֧ߧڧ�
	QSize scaledImageSize = m_image.scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation).size();
	// �����֧է֧ݧڧ� ��ѧ�����ߧڧ� ��� �ݧ֧ӧ�ԧ� �� �ӧ֧��ߧ֧ԧ� �ܧ�ѧק�
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
	// �����֧է֧ݧڧ� ��������ڧ� ��ҧݧѧ��� ��ҧ�֧٧ܧ� ��� ���ߧ��֧ߧڧ� �� �ڧ���էߧ�ާ� �ڧ٧�ҧ�ѧا֧ߧڧ�
	float xScale = (float)m_image.width() / scaledImageSize.width();
	float yScale = (float)m_image.height() / scaledImageSize.height();
	// ���ѧ��ڧ�ѧ֧� ��ҧݧѧ��� ��ҧ�֧٧ܧ� �� ���ק��� �ܧ���֧ܧ�ڧ� ��ѧ٧ާ֧��� �ڧ���էߧ�ԧ� �ڧ٧�ҧ�ѧا֧ߧڧ�
	QRectF realSizeRect(QPointF(m_croppingRect.left() - leftDelta, m_croppingRect.top() - topDelta), m_croppingRect.size());
	// ... �ܧ���֧ܧ�ڧ��֧� �ݧ֧ӧ�� �� �ӧ֧��ߧڧ� �ܧ�ѧ�
	realSizeRect.setLeft((m_croppingRect.left() - leftDelta) * xScale);
	realSizeRect.setTop((m_croppingRect.top() - topDelta) * yScale);
	// ... �ܧ���֧ܧ�ڧ��֧� ��ѧ٧ާ֧�
	realSizeRect.setWidth(m_croppingRect.width() * xScale);
	realSizeRect.setHeight(m_croppingRect.height() * yScale);
	// ����ݧ��ѧ֧� ��ҧ�֧٧ѧߧߧ�� �ڧ٧�ҧ�ѧا֧ߧڧ�
	return m_image.copy(realSizeRect.toRect());
}


void ImageCropper::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);
	
	//draw picture
	{
		// ... ���էԧ�ߧڧ� �ڧ٧�ҧ�ѧا֧ߧڧ� �էݧ� ����ҧ�ѧا֧ߧڧ� ��� ��ѧ٧ާ֧�� �ӧڧէا֧��
		QPixmap scaledImage = m_image.scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
		// ... �٧ѧݧڧӧѧ֧� ����
		painter.fillRect(this->rect(), m_backgroundColor);
		// ... ��ڧ��֧� �ڧ٧�ҧ�ѧا֧ߧڧ� ��� ��֧ߧ��� �ӧڧէا֧��
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
			// ������ާ�ԧѧ�֧ݧ�ߧ�� X �ܧ���էڧߧѧ��
			int leftXCoord = m_croppingRect.left() - 2;
			int centerXCoord = m_croppingRect.center().x() - 3;
			int rightXCoord = m_croppingRect.right() - 2;
			// ������ާ�ԧѧ�֧ݧ�ߧ�� Y �ܧ���էڧߧѧ��
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
	QPointF mousePos = event->pos(); // ���ߧ��ڧ�֧ݧ�ߧ� ��֧ҧ� (�ӧڧէا֧��)
									  //
	if (!m_bMousePressed)
	{
		// ���ҧ�ѧҧ��ܧ� ��ҧ��ߧ�ԧ� �������ߧڧ�, ��.��. �ߧ� �ڧ٧ާ֧ߧ�֧��� ��ѧ٧ާ֧�
		// ��ҧݧѧ��� ��ҧ�֧٧ܧ�, �� ��ߧ� �ߧ� ��֧�֧ާ֧�ѧ֧��� ��� �ӧڧէا֧��
		m_cursorPosition = getcursorPosition(m_croppingRect, mousePos);
		updateCursorIcon(mousePos);
	}
	else if (m_cursorPosition != CursorPositionUndefined)
	{
		// ���ҧ�ѧҧ��ܧ� �է֧ۧ��ӧڧ� �ߧѧ� ��ҧݧѧ���� ��ҧ�֧٧ܧ�
		// ... ����֧է֧ݧڧ� ��ާ֧�֧ߧڧ� �ܧ������ �ާ��ܧ�
		QPointF mouseDelta;
		mouseDelta.setX(mousePos.x() - m_startMousePos.x());
		mouseDelta.setY(mousePos.y() - m_startMousePos.y());
		//
		if (m_cursorPosition != CursorPositionMiddle)
		{
			// ... �ڧ٧ާ֧ߧ�֧� ��ѧ٧ާ֧� ��ҧݧѧ��� ��ҧ�֧٧ܧ�
			QRectF newGeometry = calculateGeometry(m_lastStaticCroppingRect, m_cursorPosition, mouseDelta);
			// ... ���ݧ�٧�ӧѧ�֧ݧ� ����ѧ֧��� �ӧ�ӧ֧�ߧ��� ��ҧݧѧ��� ��ҧ�֧٧ܧ� �ߧѧڧ٧ߧѧߧܧ�
			if (!newGeometry.isNull())
				m_croppingRect = newGeometry;
		}
		else
		{
			// ... ��֧�֧ާ֧�ѧ֧� ��ҧݧѧ��� ��ҧ�֧٧ܧ�
			m_croppingRect.moveTo(m_lastStaticCroppingRect.topLeft() + mouseDelta);
		}
		// ���֧�֧�ڧ��֧� �ӧڧէا֧�
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
	// ����ݧ� ���ݧ�٧�ӧѧ�֧ݧ� ����ѧ֧��� �ӧ�ӧ֧�ߧ��� ��ҧݧѧ��� ��ҧ�֧٧ܧ� �ߧѧڧ٧ߧѧߧܧ�,
	// �ӧ�٧ӧ�ѧ�ѧ֧� null-����ާ��ԧ�ݧ�ߧڧ�
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
