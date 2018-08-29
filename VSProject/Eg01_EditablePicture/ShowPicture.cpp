#include "ShowPicture.h"

ShowPicture::ShowPicture(QWidget *parent)
	: QWidget(parent)
{
	m_pLabel = new QLabel("Label");
	m_pLabel->installEventFilter(this);
	m_pLabel->setFixedSize(50, 40);
	m_pLabel->setStyleSheet("border:2px solid red;");

	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_pLabel);

	setLayout(mainLayout);
	setMinimumSize(600, 400);
}

ShowPicture::~ShowPicture()
{
}


bool ShowPicture::eventFilter(QObject *, QEvent * event)
{
	static QPoint lastPoint;
	static bool bDrag = false;

	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* e = static_cast<QMouseEvent*>(event);
		if (e->button() == Qt::LeftButton && m_pLabel->rect().contains(e->pos()))
		{
			//left button pressed
			lastPoint = e->pos();
			bDrag = true;
		}
	}
	else if (event->type() == QEvent::MouseMove && bDrag)
	{
		QMouseEvent* e = static_cast<QMouseEvent*>(event);
		QPoint point = e->pos() - lastPoint;
		m_pLabel->move(m_pLabel->pos() + point);
	}
	else if (event->type() == QEvent::MouseButtonRelease && bDrag)
		bDrag = false;

	return false;
}