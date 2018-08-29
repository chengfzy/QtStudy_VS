#include "Eg13_CustomizedCombobox.h"
#include "RichComboBoxItem.h"
#include <QtWidgets>

Eg13_CustomizedCombobox::Eg13_CustomizedCombobox(QWidget *parent)
	: QMainWindow(parent)
{	
	m_pRichComboBox = new RichComboBox(this);
	m_pRichComboBox->setStyleSheet("QAbstractItemView::item{ height:42px;}");

	//add items
	for (int i = 0; i < 5; ++i)
	{
		RichComboBoxItem* pItem = new RichComboBoxItem(QString("Account") + QString::number(i), this);
		//connect(pItem, &RichComboBoxItem::showItem, this, &Eg13_CustomizedCombobox::showItem);

		m_pRichComboBox->addItem(pItem);
	}

#if 0
	//combobox
	m_pComboBox = new QComboBox(this);
	m_pComboBox->setModel(pListWidget->model());
	m_pComboBox->setView(pListWidget);
	m_pComboBox->setStyleSheet("QAbstractItemView::item{ height:42px;}");
	QLineEdit* pLineEdit = new QLineEdit(this);
	pLineEdit->setReadOnly(true);
	m_pComboBox->setLineEdit(pLineEdit);
	m_pComboBox->addItem()
	//m_pComboBox->setEditable(true);
	//add items
	for (int i = 0; i < 5; ++i)
	{
		RichComboBoxItem* pItem = new RichComboBoxItem(QString("Account") + QString::number(i), this);
		connect(pItem, &RichComboBoxItem::showItem, this, &Eg13_CustomizedCombobox::showItem);

		QListWidgetItem* pWidgetItem = new QListWidgetItem(pListWidget);
		pListWidget->setItemWidget(pWidgetItem, pItem);
	}
#endif

	//QComboBox
	m_pComboBox = new QComboBox(this);
	for (int i = 0; i < 5; ++i)
	{
		m_pComboBox->addItem(QString("Item %1").arg(i));
	}
	m_pComboBox->addItem("Add New Item");
	connect(m_pComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Eg13_CustomizedCombobox::updateComboItem);


	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_pRichComboBox);
	layout->addWidget(m_pComboBox);

	QWidget* pMainWidget = new QWidget(this);
	pMainWidget->setLayout(layout);
	
	setCentralWidget(pMainWidget);

}

void Eg13_CustomizedCombobox::showItem(const QString & itemText)
{
	m_pRichComboBox->setCurrentText(itemText);
	m_pRichComboBox->hidePopup();
}

void Eg13_CustomizedCombobox::updateComboItem(int index)
{
	if (index == m_pComboBox->count() - 1)
	{
		m_pComboBox->setCurrentIndex(index);
		m_pComboBox->insertItem(index, "Added Item");
	}
}
