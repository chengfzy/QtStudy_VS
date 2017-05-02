#include "CropWidget.h"

CropWidget::CropWidget(QWidget *parent)
	: QFrame(parent)
	, m_bMoving(false), m_bMouseDown(false), m_bLeft(false), m_bRight(false)
	, m_bTop(false), m_bBottom(false)
{
	setWindowFlags(Qt::FramelessWindowHint);

	setMouseTracking(true);
	setGeometry(0, 0, 400, 500);

	m_pLabel = new QLabel(this);
	m_pLabel->setMouseTracking(true);

	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(m_pLabel);
	layout->setMargin(0);
	setLayout(layout);
}

CropWidget::~CropWidget()
{
}

void CropWidget::mousePressEvent(QMouseEvent * event)
{
}

void CropWidget::mouseMoveEvent(QMouseEvent * event)
{
}

void CropWidget::mouseReleaseEvent(QMouseEvent * event)
{
}

void CropWidget::resizeEvent(QResizeEvent * event)
{
}

void CropWidget::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	QPen pen;
	QVector<qreal> dashes;
	qreal space = 3;
	dashes << 5 << space << 5 << space;
	pen.setDashPattern(dashes);
	pen.setColor(Qt::white);

	QPen pen0;
	pen0.setColor(QColor(54, 158, 254, 120));
	pen0.setWidth(2);
	painter.setPen(pen0);
	painter.drawRect(1, 0, width() - 2, width() - 2);

	painter.setPen(pen);
	int x_pos = (int)width() / 3.0;
	int y_pos = (int)height() / 3.0;
	painter.drawLine(x_pos, 0, x_pos, height());
	painter.drawLine(2 * x_pos, 0, 2 * x_pos, height());
	painter.drawLine(0, y_pos, width(), y_pos);
	painter.drawLine(0, 2 * y_pos, width(), 2 * y_pos);
	painter.drawEllipse(0, 0, width(), width());

}

QRect CropWidget::getResizeGem(QRect oldGeo, QPoint mousePoint)
{
	return QRect();
}
