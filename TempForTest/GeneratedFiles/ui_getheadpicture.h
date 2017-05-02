/********************************************************************************
** Form generated from reading UI file 'getheadpicture.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETHEADPICTURE_H
#define UI_GETHEADPICTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GetHeadPicture
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *GetHeadPicture)
    {
        if (GetHeadPicture->objectName().isEmpty())
            GetHeadPicture->setObjectName(QStringLiteral("GetHeadPicture"));
        GetHeadPicture->resize(588, 451);
        pushButton = new QPushButton(GetHeadPicture);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(160, 380, 75, 23));
        pushButton_2 = new QPushButton(GetHeadPicture);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 380, 75, 23));
        label = new QLabel(GetHeadPicture);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 50, 391, 311));

        retranslateUi(GetHeadPicture);

        QMetaObject::connectSlotsByName(GetHeadPicture);
    } // setupUi

    void retranslateUi(QWidget *GetHeadPicture)
    {
        GetHeadPicture->setWindowTitle(QApplication::translate("GetHeadPicture", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("GetHeadPicture", "OK", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("GetHeadPicture", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("GetHeadPicture", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GetHeadPicture: public Ui_GetHeadPicture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETHEADPICTURE_H
