
#include "qscreenselector.h"
#include "maindialog.h"

#include "utils/qapputils.h"
#include "winFactory/qwinfactory.h"
#include "screenOper/qscreenshort.h"

#include <QSpacerItem>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>


QScreenSelector::QScreenSelector(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("");
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    initUI();
}

void QScreenSelector::initUI()
{
    int wid,hei;

    QGridLayout *lay        = new QGridLayout(this);
    QAppIconPanel *leftwid  = NULL;
    QAppIconPanel *rightwid       = NULL;
    QAppIconPanel *all = NULL, *todo = NULL, *done = NULL;
    QAppUtils::ref().getScreenSize(wid,hei);
    QSpacerItem *hspacer1,*hspacer2,*vspacer,*vspacerTop;
    QScreenShort        *deskTop = NULL, *fundwid = NULL,*allWid,*todoWid,*doneWid;
    QTransparentWin *headw = (QTransparentWin*)QWinFactory::ref().createWindow(QWinFactory::TransWin,this);
    QHBoxLayout *hlay = new QHBoxLayout(headw);
    IconButton *closeB = QAppUtils::ref().getCloseIconBtn(headw);
    connect(closeB,SIGNAL(clicked()),this,SLOT(close()));
    headw->setMaximumHeight(50);
    hlay->addStretch();
    hlay->addWidget(closeB);
    lay->addWidget(headw,0,5,1,4);
    hspacer1 = new QSpacerItem(50,20,QSizePolicy::Preferred, QSizePolicy::Minimum);
    hspacer2 = new QSpacerItem(50,20,QSizePolicy::Preferred,QSizePolicy::Minimum);
    vspacer = new QSpacerItem(20,50,QSizePolicy::Minimum,QSizePolicy::Expanding);
    vspacerTop = new QSpacerItem(20,50,QSizePolicy::Minimum,QSizePolicy::Expanding);
    setMinimumSize( wid,hei);
    wid = wid/5 - 40;
    hei = hei/2.5;

    leftwid = dynamic_cast<QAppIconPanel*> (QWinFactory::ref().createWindow(QWinFactory::APPIconPanel,this));
    rightwid = (QAppIconPanel*)QWinFactory::ref().createWindow(QWinFactory::APPIconPanel,this);

    all = (QAppIconPanel*)QWinFactory::ref().createWindow(QWinFactory::APPIconPanel,this);
    todo = (QAppIconPanel*)QWinFactory::ref().createWindow(QWinFactory::APPIconPanel,this);
    done = (QAppIconPanel*)QWinFactory::ref().createWindow(QWinFactory::APPIconPanel,this);

    deskTop = dynamic_cast<QScreenShort*>(
                QWinFactory::ref().createWindow(QWinFactory::ScreenShort,this));
    fundwid = dynamic_cast<QScreenShort*>(
                QWinFactory::ref().createWindow(QWinFactory::ScreenShort,this));
    allWid = dynamic_cast<QScreenShort*>(
                QWinFactory::ref().createWindow(QWinFactory::ScreenShort,this));
    todoWid = dynamic_cast<QScreenShort*>(
                QWinFactory::ref().createWindow(QWinFactory::ScreenShort,this));
    doneWid = dynamic_cast<QScreenShort*>(
                QWinFactory::ref().createWindow(QWinFactory::ScreenShort,this));

    connect(deskTop,SIGNAL(screenClicked(QString)),this,SLOT(slot_selectDesk(QString)));
    connect(fundwid,SIGNAL(screenClicked(QString)),this,SLOT(slot_selectDesk(QString)));

    connect(allWid,SIGNAL(screenClicked(QString)),this,SLOT(slot_showall(QString)));
    connect(todoWid,SIGNAL(screenClicked(QString)),this,SLOT(slot_showtodo(QString)));
    connect(doneWid,SIGNAL(screenClicked(QString)),this,SLOT(slot_showdone(QString)));

    deskTop->setMaximumSize(wid,wid);
    fundwid->setMaximumSize(wid,wid);
    deskTop->setMinimumSize(wid,wid);
    fundwid->setMinimumSize(wid,wid);
    leftwid->addApp(QPixmap(":/ui/computer.png"),LOCAL("我的电脑"),"");
    leftwid->addApp(QPixmap(":/ui/control.png"),LOCAL("控制面板"),"");
    leftwid->addApp(QPixmap(":/ui/cycle.png"),LOCAL("回收站"),"");

    leftwid->resize(wid,hei);
    rightwid->resize(wid,hei);
    all->setStyleSheet("border-image:url(:/ui/alltask.png)");
    todo->setStyleSheet("border-image:url(:/ui/todo.png)");
    done->setStyleSheet("border-image:url(:/ui/done.png)");
    rightwid->setStyleSheet("border-image:url(:/ui/fund.png)");

    deskTop->setWidget(leftwid);
    fundwid->setWidget(rightwid);
    allWid->setWidget(all);
    todoWid->setWidget(todo);
    doneWid->setWidget(done);

    deskTop->setWindowTitle(LOCAL("系统桌面"));
    fundwid->setWindowTitle(LOCAL("财政桌面"));
    allWid->setWindowTitle(LOCAL("事项管理"));
    todoWid->setWindowTitle(LOCAL("事项管理"));
    doneWid->setWindowTitle(LOCAL("事项管理"));
    lay->addItem(vspacerTop,1,0,1,1);

    lay->addItem(hspacer1,2,0,1,1);
    lay->addWidget(deskTop,2,1,1,1);
    lay->addWidget(fundwid,2,2,1,1);
    lay->addItem(hspacer2,2,3,1,1);

    lay->addWidget(allWid,2,3,1,1);
    lay->addWidget(todoWid,2,4,1,1);
    lay->addWidget(doneWid,2,5,1,1);

//    lay->addItem(new QSpacerItem(50,20,QSizePolicy::Preferred, QSizePolicy::Minimum)
//                 ,3,0,1,1);

    lay->addItem(new QSpacerItem(20,70,QSizePolicy::Preferred, QSizePolicy::Minimum)
                 ,3,0,1,1);

    lay->addItem(vspacer,4,0,1,1);
    lay->addItem(new QSpacerItem(20,80,QSizePolicy::Minimum,QSizePolicy::Expanding),5,0,1,1);
}

void QScreenSelector::paintEvent(QPaintEvent *)
{

    QPainter p(this);
    p.fillRect(rect(),QColor(200,200,200,90));

}
void QScreenSelector::slot_selectDesk(QString title)
{
    setVisible(false);
    if ( title == LOCAL("系统桌面"))
    {
        MainDialog::ref().getStackedWidget()->setCurrentIndex(0);
    }else
    {
        MainDialog::ref().getStackedWidget()->setCurrentIndex(1);
    }
}
void QScreenSelector::slot_showall(QString)
{
    setVisible(false);
    MainDialog::ref().m_all->showMaximized();
}
void QScreenSelector::slot_showtodo(QString)
{
    setVisible(false);
    MainDialog::ref().m_todo->showMaximized();
}
void QScreenSelector::slot_showdone(QString)
{
    setVisible(false);
    MainDialog::ref().m_done->showMaximized();
}
