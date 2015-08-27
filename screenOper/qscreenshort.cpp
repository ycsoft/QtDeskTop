#include "qscreenshort.h"
#include "winFactory/qwinfactory.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QDebug>
#include <QVBoxLayout>
#include <QPalette>

QScreenShort::QScreenShort(QWidget *parent) : QWidget(parent),m_hlay(NULL),m_center(NULL)
  ,m_lbtitle(NULL)
{
    m_pressed = false;
    m_entered = false;
    setWindowFlags(Qt::FramelessWindowHint);
    initUI();
    setAttribute(Qt::WA_TranslucentBackground);
}
void QScreenShort::setWidget(QWidget *wid)
{
    if ( NULL != m_hlay )
        m_hlay->addWidget(wid);
}
void QScreenShort::setWindowTitle(const QString &title)
{
    m_lbtitle->setText(title);
}

void QScreenShort::initUI()
{
    QStringList stricon;
    QVBoxLayout *vlay = new QVBoxLayout(this);
    m_lbtitle = new QLabel(this);
    m_lbtitle->setStyleSheet("font: 75 18pt \"Aharoni\";"
                             "color: rgb(245, 245, 245);");
    m_lbtitle->setAttribute(Qt::WA_TranslucentBackground);

    m_center = QWinFactory::ref().createWindow(QWinFactory::Widget,this);
    m_center->setAttribute(Qt::WA_TranslucentBackground);
    m_hlay = new QHBoxLayout(m_center);
    m_hlay->setContentsMargins(10,10,10,10);

    stricon <<":/ui/btn_close_normal.png"
            <<":/ui/btn_close_highlight.png"
            <<":/ui/btn_close_down.png";
    IconButton *closeB = new IconButton(this,stricon[0],stricon[1],stricon[2]);
    connect(closeB,SIGNAL(clicked()),this,SLOT(hide()));
    m_lbtitle->setText("Windows");

    QTransparentWin *tipw = (QTransparentWin*)QWinFactory::ref().createWindow(QWinFactory::TransWin,this);
    QHBoxLayout *hlay = new QHBoxLayout(tipw);
    tipw->setMaximumHeight(40);
    tipw->setAttribute(Qt::WA_TranslucentBackground);
    hlay->setContentsMargins(5,0,3,0);
    hlay->addWidget(m_lbtitle);
    hlay->addStretch();
    hlay->addWidget(closeB);
    vlay->setContentsMargins(0,0,0,0);
    vlay->setSpacing(2);
    vlay->addWidget(tipw);
    vlay->addWidget(m_center);

}

void QScreenShort::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QStyleOption op;

    op.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);

    if ( m_entered )
    {
        QPen pen(Qt::NoPen);
        QBrush brush(QColor(100,100,0));
        QRect rt = rect();
        rt.setX( rt.x() + 20);
        rt.setY( rt.y() - 20);
        rt.setWidth( rt.width() - 40);
        rt.setHeight( rt.height() - 40);
        p.setBrush(brush);
        p.setPen(pen);
        p.drawRect(rect());
    }
    else
    {
//        QPalette pal = palette();
//        pal.setColor(QPalette::Background,QColor(0x00,0xff,0x00,0x00));
//        setPalette(pal);
    }
}
void QScreenShort::enterEvent(QEvent *)
{
    m_entered = true;
    update();
}
void QScreenShort::leaveEvent(QEvent *)
{
    m_entered = false;
    update();
}
void QScreenShort::mousePressEvent(QMouseEvent *evt)
{
    emit screenClicked(m_lbtitle->text());
}
