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
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QHBoxLayout>
#include <QPalette>

#include "taskbar.h"
#include "skin/iconbutton.h"
#include "skin/deskicon.h"

#define LOCAL(x)    QString::fromLocal8Bit(x)


QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:

    QHBoxLayout *taskLay;
    QVBoxLayout *mainLay;

    QGridLayout *gridLay;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        MainDialog->resize(400, 300);

        MainDialog->setStyleSheet("QDialog#MainDialog{border-image: url(:/ui/desk.jpg);}");

        //
        QWidget *content = new QWidget(MainDialog);
        gridLay = new QGridLayout( content );
        gridLay->setSpacing(40);

//        IconButton *compute1 = new IconButton(content,":/ui/computer.png",":/ui/computer.png",":/ui/computer.png");
//        IconButton *compute2 = new IconButton(content,":/ui/computer.png",":/ui/computer.png",":/ui/computer.png");
//        IconButton *compute3 = new IconButton(content,":/ui/computer.png",":/ui/computer.png",":/ui/computer.png");
        DeskIcon    *compute1 =new DeskIcon(0,":/ui/computer.png");
        DeskIcon    *compute2 =new DeskIcon(0,":/ui/computer.png");
        DeskIcon    *compute3 =new DeskIcon(0,":/ui/computer.png");

        compute1->setIcon(":/ui/computer.png");

        compute1->setIconText(LOCAL("我的电脑"));
        compute2->setIconText(LOCAL("我的电脑"));
        compute3->setIconText(LOCAL("我的电脑"));

        gridLay->addWidget(compute1,0,0,1,1,Qt::AlignTop | Qt::AlignLeft);
        gridLay->addWidget(compute2,1,0,1,1,Qt::AlignTop | Qt::AlignLeft);
        gridLay->addWidget(compute3,2,0,1,1,Qt::AlignTop | Qt::AlignLeft);


        mainLay = new QVBoxLayout(MainDialog);
        mainLay->setContentsMargins(0,0,0,0);
        mainLay->addWidget(content);
        mainLay->addStretch();
        mainLay->addWidget( taskBar(MainDialog) );


        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    QWidget* taskBar(QDialog *MainDialog)
    {
        TaskBar *task = new TaskBar(MainDialog);

        task->setAttribute(Qt::WA_TranslucentBackground,true);
        taskLay = new QHBoxLayout(task);
        task->setMaximumHeight(100);

        DeskIcon    *compute1 =new DeskIcon(task,":/ui/computer.png");

        taskLay->setSpacing(0);
        taskLay->setContentsMargins(0,0,0,0);
        taskLay->addWidget(compute1,0,Qt::AlignLeft);
        task->setLayout(taskLay);
        return task;
    }

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "MainDialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
