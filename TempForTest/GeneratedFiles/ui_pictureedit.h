/********************************************************************************
** Form generated from reading UI file 'pictureedit.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTUREEDIT_H
#define UI_PICTUREEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PictureEditClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PictureEditClass)
    {
        if (PictureEditClass->objectName().isEmpty())
            PictureEditClass->setObjectName(QStringLiteral("PictureEditClass"));
        PictureEditClass->resize(688, 520);
        centralWidget = new QWidget(PictureEditClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 0, 471, 341));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 380, 75, 23));
        PictureEditClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PictureEditClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 688, 23));
        PictureEditClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PictureEditClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PictureEditClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PictureEditClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PictureEditClass->setStatusBar(statusBar);

        retranslateUi(PictureEditClass);

        QMetaObject::connectSlotsByName(PictureEditClass);
    } // setupUi

    void retranslateUi(QMainWindow *PictureEditClass)
    {
        PictureEditClass->setWindowTitle(QApplication::translate("PictureEditClass", "PictureEdit", Q_NULLPTR));
        label->setText(QApplication::translate("PictureEditClass", "TextLabel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PictureEditClass", "Load", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PictureEditClass: public Ui_PictureEditClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREEDIT_H
