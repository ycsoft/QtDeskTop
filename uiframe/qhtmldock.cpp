#include "qhtmldock.h"
#include <QHBoxLayout>

#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QDebug>

QHtmlDock::QHtmlDock(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void QHtmlDock::paintEvent(QPaintEvent *evt)
{
    QPainter p(this);
    QStyleOption op;
    op.init(this);

    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);
}

void QHtmlDock::initUI()
{
    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->setContentsMargins(0,0,0,0);
    vlay->setSpacing(0);
    setObjectName("htmldock");
    setStyleSheet("QWidget#mainwim{border-image: url(:/ui/mac-desk.jpg);}");

    m_web = new QHFWebView(this);
    vlay->addWidget(m_web,0,Qt::AlignHCenter);
    m_web->load(QUrl("html/dock.html"));
    m_web->setTransparent(true);

}
void QHtmlDock::mousePressEvent(QMouseEvent *evt)
{
    if ( Qt::LeftButton == evt->button())
    {

        m_pressed = true;
        m_movePoint = evt->globalPos() - pos();
        qDebug()<<"Press";
    }
}

void QHtmlDock::mouseReleaseEvent(QMouseEvent *evt)
{
    m_pressed = false;
}

void QHtmlDock::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_pressed)
    {
        move(evt->globalPos() - m_movePoint);
    }
}
