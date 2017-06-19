#include "RichComboBox.h"

RichComboBox::RichComboBox(QWidget *parent)
	: QComboBox(parent)
{
	//list widget
	m_pListWidget = new QListWidget(this);
	
	//model and view
	setModel(m_pListWidget->model());
	setView(m_pListWidget);

	setEditable(true);
	////set line edit
	//m_pLineEdit = new QLineEdit(this);
	//m_pLineEdit->setReadOnly(true);
	//setLineEdit(m_pLineEdit);


	//actions
	//connect(m_pLineEdit, &QLineEdit::wheelEvent, this, &RichComboBox::wheelEvent);
	//connect(m_pListWidget, &QListWidget::itemPressed, this, &RichComboBox::setShowText);
	connect(this, static_cast<void (RichComboBox::*)(int)>(&RichComboBox::currentIndexChanged), this, [this](int index)
	{
		//m_pListWidget->itemAt()
		this->setEditText(QString::number(index));
	});
}

RichComboBox::~RichComboBox()
{
}

void RichComboBox::addItem(RichComboBoxItem* item)
{
	QListWidgetItem* pListWidgetItem = new QListWidgetItem(m_pListWidget);
	m_pListWidget->setItemWidget(pListWidgetItem, item);

	connect(item, &RichComboBoxItem::itemClicked, this, &RichComboBox::setShowText);
}

void RichComboBox::setShowText(const QString& text)
{
	setEditText(text);
	//m_pLineEdit->setText(text);
	//this->hidePopup();
}
