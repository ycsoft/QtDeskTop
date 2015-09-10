/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditUsr;
    QPushButton *pushButtonCA;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEditPwd;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonCancel;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QCommandLinkButton *commandLinkButton;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        MainDialog->resize(318, 279);
        MainDialog->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(MainDialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(MainDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(widget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(230, 40));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(60, 0));
        label_4->setStyleSheet(QString::fromUtf8("font: 28pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";\n"
"color: rgb(255, 0, 0);\n"
""));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        lineEditUsr = new QLineEdit(widget);
        lineEditUsr->setObjectName(QString::fromUtf8("lineEditUsr"));

        horizontalLayout->addWidget(lineEditUsr);

        pushButtonCA = new QPushButton(widget);
        pushButtonCA->setObjectName(QString::fromUtf8("pushButtonCA"));
        pushButtonCA->setMaximumSize(QSize(30, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/UI/certificate.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCA->setIcon(icon);

        horizontalLayout->addWidget(pushButtonCA);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_3);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(0, 0));
        comboBox->setEditable(true);

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        lineEditPwd = new QLineEdit(widget);
        lineEditPwd->setObjectName(QString::fromUtf8("lineEditPwd"));
        lineEditPwd->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(lineEditPwd);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonLogin = new QPushButton(widget);
        pushButtonLogin->setObjectName(QString::fromUtf8("pushButtonLogin"));
        pushButtonLogin->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";"));

        horizontalLayout_4->addWidget(pushButtonLogin);

        pushButtonCancel = new QPushButton(widget);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\346\245\267\344\275\223\";"));

        horizontalLayout_4->addWidget(pushButtonCancel);


        horizontalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        commandLinkButton = new QCommandLinkButton(widget);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setMinimumSize(QSize(60, 0));
        commandLinkButton->setMaximumSize(QSize(100, 16777215));
        commandLinkButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(commandLinkButton);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(widget);


        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "\350\264\242\346\224\277\345\256\211\345\205\250\351\200\232\350\241\214\350\257\201", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainDialog", "\350\264\242\346\224\277\351\200\232\350\241\214\350\257\201", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainDialog", "\347\234\201\344\273\275\350\257\201\345\217\267\347\240\201", 0, QApplication::UnicodeUTF8));
        lineEditUsr->setPlaceholderText(QApplication::translate("MainDialog", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
        pushButtonCA->setText(QString());
        label_3->setText(QApplication::translate("MainDialog", "\350\241\214\346\224\277\345\214\272\345\210\222  ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainDialog", "\345\257\206    \347\240\201  ", 0, QApplication::UnicodeUTF8));
        lineEditPwd->setPlaceholderText(QApplication::translate("MainDialog", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        pushButtonLogin->setText(QApplication::translate("MainDialog", "\347\231\273\351\231\206", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("MainDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        commandLinkButton->setText(QApplication::translate("MainDialog", "\351\253\230\347\272\247\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
