#include "TrackLabel.h"

TrackLabel::TrackLabel(QString title, QWidget *parent)
	: m_szTitle(title)
	, QWidget(parent)
{
	setupUI();
	setFixedSize(100, 100);
}

TrackLabel::~TrackLabel()
{
}

void TrackLabel::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	const int nTimeRectHeight = height();

	//draw backgroud rect
	painter.save();
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(Qt::darkGray));
	painter.drawRect(this->rect());
	painter.restore();
}

void TrackLabel::setupUI()
{
	//title lable
	m_pTitleLabel = new QLabel(m_szTitle);


	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(m_pTitleLabel);

	setLayout(pMainLayout);
}
