#include "taskbar.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>

TaskBar::TaskBar(QWidget *parent) :
    QWidget(parent)
{
    //setAttribute(Qt::WA_TranslucentBackground,true);
//    setStyleSheet("background-color: rgb(255, 237, 246);");
    setWindowFlags(Qt::FramelessWindowHint);
}

void TaskBar::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    QStyleOption op;

    op.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&op,&painter,this);
    painter.fillRect(rect(),QColor(25, 25, 25));
}
