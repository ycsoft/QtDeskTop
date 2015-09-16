#include "qsimplemode.h"
#include "utils/defines.h"

#include "maindialog.h"

#include <QHBoxLayout>


#include <data/qtododata.h>
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include <QDebug>

QSimpleMode::QSimpleMode(QWidget *parent) : QWidget(parent)
{
    initUI();
    resize(700,500);
}

void QSimpleMode::initUI()
{
    QHBoxLayout *hlay = new QHBoxLayout(this);
    web = new QHFWebView(this);

    web->setContextMenuPolicy(Qt::NoContextMenu);
    hlay->setContentsMargins(0,0,0,0);
    hlay->addWidget(web);
    web->load(QUrl("html/test.html"));

    QWebSettings    *webSetting = web->page()->settings();
    webSetting->setAttribute(QWebSettings::JavascriptEnabled,true);

    connect(web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addObject()));

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
