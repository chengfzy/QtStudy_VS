#include "Eg11_GraphicsView.h"
#include <QtWidgets/QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//Eg11_GraphicsView w;
	//w.show();
	
	//Simple QGraphicsView Example
#if 0
	//Simple Text
	QGraphicsSimpleTextItem* pSimpleTextItem = new QGraphicsSimpleTextItem();
	pSimpleTextItem->setText("Graphics Simple Text");
	//font
	QFont font = pSimpleTextItem->font();
	font.setPixelSize(20);
	font.setItalic(true);
	font.setUnderline(true);
	pSimpleTextItem->setFont(font);
	pSimpleTextItem->setBrush(QBrush(QColor(0, 160, 230)));

	//Text
	QGraphicsTextItem* pTextItem = new QGraphicsTextItem();
	pTextItem->setPlainText("Text Item");
	pTextItem->setDefaultTextColor(QColor(0, 100, 230));
	pTextItem->setFont(font);
	pTextItem->setTextInteractionFlags(Qt::TextInteractionFlag::TextEditorInteraction);

	//scene
	QGraphicsScene* pScene = new QGraphicsScene();
	pScene->addItem(pSimpleTextItem);
	pScene->addItem(pTextItem);

	//view
	QGraphicsView* pView = new QGraphicsView();
	pView->setScene(pScene);
	pView->setStyleSheet("border:none;");
	pView->show();
#endif

	//basic widget
	QLabel* pPixmapLabel = new QLabel();
	pPixmapLabel->setText("IMAGE");

	QLineEdit* pAccountLineEdit = new QLineEdit();
	pAccountLineEdit->setPlaceholderText("QQ/Tel/Email");
	QLineEdit* pPasswordLineEdit = new QLineEdit();
	pPasswordLineEdit->setPlaceholderText("Password");
	pPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

	QCheckBox* pRememberCheckBox = new QCheckBox();
	pRememberCheckBox->setText("Remeber Password");
	QCheckBox* pAutoLoginCheckBox = new QCheckBox();
	pAutoLoginCheckBox->setText("Auto Login");

	QPushButton* pLoginButton = new QPushButton();
	pLoginButton->setText("Login");
	QPushButton* pRegisterButton = new QPushButton();
	pRegisterButton->setText("Register");
	QPushButton* pForgotButton = new QPushButton();
	pForgotButton->setText("Forget");

	//add to widget
	QGraphicsScene* m_pScene = new QGraphicsScene();
	QGraphicsProxyWidget* pPixmapWidget = m_pScene->addWidget(pPixmapLabel);
	QGraphicsProxyWidget* pAccountWidget = m_pScene->addWidget(pAccountLineEdit);
	QGraphicsProxyWidget* pPasswordWidget = m_pScene->addWidget(pPasswordLineEdit);
	QGraphicsProxyWidget* pRememberWidget = m_pScene->addWidget(pRememberCheckBox);
	QGraphicsProxyWidget* pAutoLogoinWidget = m_pScene->addWidget(pAutoLoginCheckBox);
	QGraphicsProxyWidget* pLoginWidget = m_pScene->addWidget(pLoginButton);
	QGraphicsProxyWidget* pRegisterWidget = m_pScene->addWidget(pRegisterButton);
	QGraphicsProxyWidget* pForgetWidget = m_pScene->addWidget(pForgotButton);

	//add to layout
	QGraphicsGridLayout* pLayout = new QGraphicsGridLayout();
	pLayout->addItem(pPixmapWidget, 0, 0, 3, 1);
	pLayout->addItem(pAccountWidget, 0, 1, 1, 2);
	pLayout->addItem(pPasswordWidget, 1, 1, 1, 2);
	pLayout->addItem(pRememberWidget, 2, 1, 1, 1);
	pLayout->addItem(pAutoLogoinWidget, 2, 2, 1, 1);
	pLayout->addItem(pLoginWidget, 3, 1, 1, 2);
	pLayout->addItem(pRegisterWidget, 0, 3, 1, 1);
	pLayout->addItem(pForgetWidget, 1, 3, 1, 1);
	pLayout->setHorizontalSpacing(10);
	pLayout->setVerticalSpacing(10);
	pLayout->setContentsMargins(10, 10, 10, 10);

	QGraphicsWidget* pWidget = new QGraphicsWidget();
	pWidget->setLayout(pLayout);

	//add item to scene
	m_pScene->addItem(pWidget);

	//set view
	QGraphicsView* m_pView = new QGraphicsView();
	m_pView->setScene(m_pScene);
	m_pView->show();

	return a.exec();
}
