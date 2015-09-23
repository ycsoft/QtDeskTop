#include "qsimplemode.h"
#include "utils/defines.h"
#include "utils/qapputils.h"
#include "qhtmldock.h"
#include "maindialog.h"
#include "qhtmldock.h"

#include <QHBoxLayout>
#include <data/qtododata.h>
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>


QSimpleMode::QSimpleMode(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    initUI();
}

void QSimpleMode::initUI()
{
    int wid,hei;
    QVBoxLayout *hlay = new QVBoxLayout(this);
    web = new QHFWebView(this);
    QAppUtils::ref().getScreenSize(wid,hei);
    hlay->setContentsMargins(0,0,0,0);
    hlay->setSpacing(0);
    hlay->addWidget(web);
    web->load(QUrl("html/tasksManager.html"));
    QWebSettings    *webSetting = web->page()->settings();
    webSetting->setAttribute(QWebSettings::JavascriptEnabled,true);
    connect(web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addObject()));

    //QAppUtils::ref().getScreenSize(wid,hei);
//    int x = (wid - DOCK_WID)/2;
//    int y = hei - DOCK_HEI;

//    QHtmlDock *dock = new QHtmlDock(this);
//    dock->setAttribute(Qt::WA_TranslucentBackground);
//    dock->move(x,y);
//    dock->show();
}
void QSimpleMode::addObject()
{
    web->page()->mainFrame()->addToJavaScriptWindowObject("QSimpleMode",this);
}
QStringList QSimpleMode::invoke()
{
    QStringList list;
    list<<"1"<<"2"<<"3";
    return list;
}
QStringList QSimpleMode::getAllCanDoList()
{
    return QStringList()<<"1";
}
QString     QSimpleMode::get(QString sql)
{
    QString res =  LOCAL("<h3>项目支出明细2</h3><p>单位：国库处</p><p>审核："
                         "张三</p><p>摘要:2014年度总共支付543万元，其中....</p>");
    return res;
}

void QSimpleMode::contextMenuEvent(QContextMenuEvent *evt)
{
    QMenu *menu = new QMenu(this);

    QAction *act1 = new QAction(LOCAL("返回完全模式"),this);
    QAction *act2 = new QAction(LOCAL("关闭"),this);

    connect(act1,SIGNAL(triggered()),this,SLOT(returnToAll()));
    connect(act2,SIGNAL(triggered()),this,SLOT(returnToAll()));
    menu->addAction(act1);
    menu->addAction(act2);

    menu->exec(cursor().pos());
}
void QSimpleMode::returnToAll()
{
    MainDialog::ref().getStackedWidget()->setCurrentIndex(0);
}
void QSimpleMode::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QStyleOption op;
    op.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);

    p.fillRect(rect(),QColor(100,0,100,50));
}
