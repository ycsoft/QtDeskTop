/********************************************************************************
** Form generated from reading UI file 'addnotifymsg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNOTIFYMSG_H
#define UI_ADDNOTIFYMSG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddNotifyMsg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *AddNotifyMsg)
    {
        if (AddNotifyMsg->objectName().isEmpty())
            AddNotifyMsg->setObjectName(QString::fromUtf8("AddNotifyMsg"));
        AddNotifyMsg->resize(263, 147);
        verticalLayout = new QVBoxLayout(AddNotifyMsg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(AddNotifyMsg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("gridline-color: rgb(85, 85, 127);\n"
"background-color: rgb(85, 85, 127);"));

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AddNotifyMsg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(AddNotifyMsg);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(AddNotifyMsg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        label->raise();
        comboBox->raise();
        pushButton->raise();
        comboBox->raise();
        label_2->raise();

        retranslateUi(AddNotifyMsg);

        QMetaObject::connectSlotsByName(AddNotifyMsg);
    } // setupUi

    void retranslateUi(QDialog *AddNotifyMsg)
    {
        AddNotifyMsg->setWindowTitle(QApplication::translate("AddNotifyMsg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        label->setText(QApplication::translate("AddNotifyMsg", "\345\272\224\347\224\250\347\250\213\345\272\217", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("AddNotifyMsg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddNotifyMsg: public Ui_AddNotifyMsg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNOTIFYMSG_H
