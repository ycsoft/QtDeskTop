#include "qhfscroll.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>

QHFScroll::QHFScroll(QWidget *parent) : QScrollArea(parent)
{
//    setAttribute(Qt::WA_TranslucentBackground);
//    setStyleSheet("QScrollArea {background-color:transparent;}");
//    viewport()->setStyleSheet("{background-color:transparent;}");
}


void QHFScroll::paintEvent(QPaintEvent *evt)
{
    Q_UNUSED(evt);

    QPainter p(this);
    QStyleOption op;

    op.init(this);

    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);

    p.fillRect(rect(),QColor(100,200,50,50));

}
