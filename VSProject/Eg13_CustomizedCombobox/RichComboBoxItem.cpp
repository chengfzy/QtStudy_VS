#include "RichComboBoxItem.h"
#include <QtWidgets>

RichComboBoxItem::RichComboBoxItem(const QString& text, QWidget *parent)
	: QWidget(parent)
	, m_bMousePressed(false)
{
	//show label
	m_pLabel = new QLabel(text,this);

	//delete button
	m_pButton = new QPushButton(this);
	QPixmap icon(tr(":/icon/delete"));
	m_pButton->setIcon(icon);
	m_pButton->setIconSize(QSize(16, 16));
	m_pButton->setStyleSheet("background:transparent;");
	
	QHBoxLayout* pLayout = new QHBoxLayout(this);
	pLayout->addWidget(m_pLabel);
	pLayout->addStretch();
	pLayout->addWidget(m_pButton);
	pLayout->setSpacing(5);
	pLayout->setContentsMargins(5, 5, 5, 5);
	
	setLayout(pLayout);
}

RichComboBoxItem::~RichComboBoxItem()
{
}

QString RichComboBoxItem::itemString() const
{
	return m_pLabel->text();
}

void RichComboBoxItem::setLabelString(const QString & labelStr)
{
	m_pLabel->setText(labelStr);
}

void RichComboBoxItem::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
		m_bMousePressed = true;
}

void RichComboBoxItem::mouseReleaseEvent(QMouseEvent * event)
{
	if (m_bMousePressed)
	{
		emit itemClicked(m_pLabel->text());
		m_bMousePressed = false;
	}
}
