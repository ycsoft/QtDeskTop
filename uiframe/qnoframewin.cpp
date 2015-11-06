#include "qnoframewin.h"

#include "skin/iconbutton.h"
#include "utils/qapputils.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>

#define LOCAL(x) QString::fromLocal8Bit(x)

QNoFrameWin::QNoFrameWin(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    initUI();

    m_isPressed = false;
}

void QNoFrameWin::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_isPressed )
    {
        move(evt->globalPos() - m_pressPoint);
    }
}

void QNoFrameWin::mousePressEvent(QMouseEvent *evt)
{
    if ( evt->button() == Qt::LeftButton )
    {
        m_isPressed = true;
        m_pressPoint = evt->pos();
    }
}

void QNoFrameWin::mouseReleaseEvent(QMouseEvent *)
{
    m_isPressed = false;
}

void QNoFrameWin::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QStyleOption opt;

    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

//    painter.fillRect(rect(),QColor(100,30,200,30));

}

void QNoFrameWin::setWindowTitle(const QString &title)
{
    if ( NULL != m_lbtitle )
    {
        m_lbtitle->setText(title);
    }
}
void QNoFrameWin::setTitleStyle(const QString &style)
{
    m_lbtitle->setStyleSheet(style);
}

void QNoFrameWin::initUI()
{
    QStringList  stricon;
    QVBoxLayout *vlay = new QVBoxLayout(this);
    QWidget     *tipwid = new QWidget(this);
    QHBoxLayout *hlay = new QHBoxLayout(tipwid);
    int         width,height;

    QAppUtils::ref().getScreenSize(width,height);
    m_lbtitle = new QLabel(this);
    stricon <<":/ui/btn_close_normal.png"
            <<":/ui/btn_close_highlight.png"
            <<":/ui/btn_close_down.png";
    IconButton *closeB = new IconButton(this,stricon[0],stricon[1],stricon[2]);

    vlay->setContentsMargins(2,5,2,0);
    hlay->setContentsMargins(0,0,0,0);
    m_lbtitle->setText(LOCAL("暂时无消息"));
    m_lbtitle->setWordWrap(true);
    connect(closeB,SIGNAL(pressed()),this,SLOT(close()));

    hlay->addStretch();
    hlay->addWidget(m_lbtitle);
    hlay->addStretch();
    hlay->addWidget(closeB);

    vlay->addWidget(tipwid);
    m_centerpanel = new QWidget(this);
    m_centerpanel->setWindowOpacity(1.0);
//    m_centerpanel->setStyleSheet("background-color: rgb(230, 230, 230);");
    m_gridLay = new QGridLayout(m_centerpanel);
    //m_hlay = new QHBoxLayout(m_centerpanel);
    vlay->addWidget(m_centerpanel);
    tipwid->setMaximumHeight(50);
}
