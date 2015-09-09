#include "qsimplemode.h"

#include <QHBoxLayout>


#include <data/qtododata.h>
#include <QMessageBox>

QSimpleMode::QSimpleMode(QWidget *parent) : QWidget(parent)
{
    initUI();
    resize(700,500);
}

void QSimpleMode::initUI()
{
    QHBoxLayout *hlay = new QHBoxLayout(this);
    web = new QWebView(this);

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
QString QSimpleMode::invoke()
{
    QMessageBox::information(this,"123","456",0);
    return "hello";
}
