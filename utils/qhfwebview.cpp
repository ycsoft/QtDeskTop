#include "qhfwebview.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QPalette>

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

void QHFWebView::setTransparent(bool )
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base,Qt::transparent);

    this->page()->setPalette(palette);
    setAttribute(Qt::WA_OpaquePaintEvent,false);
}
