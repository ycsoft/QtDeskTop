#include "qhfwebview.h"
#include "jsCore/qjscore.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QPalette>
#include <QMouseEvent>
#include <QWebSettings>
#include <QWebFrame>

QHFWebView::QHFWebView(QWidget *parent) : QWebView(parent)
{

}


//void QHFWebView::paintEvent(QPaintEvent *evt)
//{
//    QPainter p;
//    QStyleOption op;

//    //QWebView::paintEvent(evt);

//    op.init(this);
//    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);
//}

void QHFWebView::mouseDoubleClickEvent(QMouseEvent *evt)
{
    evt->ignore();
}

void QHFWebView::setTransparent(bool )
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base,Qt::transparent);

    this->page()->setPalette(palette);
    setAttribute(Qt::WA_OpaquePaintEvent,false);
}

void QHFWebView::registerObject()
{
    QJSCore *core = QJSCore::ref();
    page()->mainFrame()->addToJavaScriptWindowObject("Qt",core);
}

void QHFWebView::load(const QUrl &url)
{
    QWebView::load(url);
    QWebSettings *sets = this->page()->settings();
    sets->setAttribute(QWebSettings::JavascriptEnabled,true);
    sets->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);
    sets->setAttribute(QWebSettings::LocalStorageEnabled,true);
    connect(page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(registerObject()));
}
