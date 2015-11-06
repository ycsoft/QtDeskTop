#include "qtiptxt.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QStyle>
#include <QDebug>

QTipTxt::QTipTxt(QWidget *parent) :
    QWidget(parent)
{
    setupUi();
    _benter = false;
//    setMinimumHeight(100);
//    setMaximumHeight(200);
}

void QTipTxt::setupUi()
{
    QHBoxLayout *hlay = new QHBoxLayout(this);

    _lb_ico = new QLabel(this);
    _lb_txt = new QLabel(this);

    _lb_txt->setMinimumHeight(80);
    _lb_txt->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    _lb_ico->setAttribute(Qt::WA_TranslucentBackground);
    _lb_txt->setAttribute(Qt::WA_TranslucentBackground);

    setIcon(":/ui/flag.png");
    hlay->setSpacing(10);
    hlay->addWidget(_lb_ico);
    hlay->addWidget(_lb_txt,0,Qt::AlignLeft | Qt::AlignTop);
    hlay->addStretch();

}

void QTipTxt::setText(QString txt)
{
    _lb_txt->setText(txt);
    _lb_txt->setWordWrap(true);
    _lb_txt->setToolTip(txt);
}

void QTipTxt::setIcon(QString iconpath)
{
    _lb_ico->setPixmap(QPixmap(iconpath));
}

void QTipTxt::paintEvent(QPaintEvent *evt)
{
    QPainter p(this);
    QStyleOption op;
    op.init(this);

    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);

    if (_benter)
    {
//        QColor color(126, 67, 121,50);
//        QBrush brush(color);
//        QPen pen(Qt::NoPen);
//        p.setBrush(brush);
//        p.setPen(pen);
//        //p.fillRect(rect(),color);
//        p.drawRoundedRect(rect(),5,5);

    }
}

void QTipTxt::enterEvent(QEvent *evt)
{
    _benter = true;
    update();
}
void QTipTxt::leaveEvent(QEvent *evt)
{
    _benter = false;
    update();
}
