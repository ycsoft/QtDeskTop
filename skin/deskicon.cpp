#include "deskicon.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QMouseEvent>

#include <Windows.h>
#include <ShellAPI.h>

DeskIcon::DeskIcon(QWidget *parent,QString icon, int type) :
    QPushButton(parent),m_type(type)
{
    m_lb_icon = new QLabel(this);
    m_lb_icon->setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout *vlay = new QVBoxLayout(this);

    if ( type != PATH_NAME)
    {
        m_icon.load(icon);
        m_icon = m_icon.scaled(40,40);
    }else
    {
        QFileInfo info(icon);
        QFileIconProvider provider;
        QIcon icon = provider.icon(info);
        m_icon = icon.pixmap(20,20);
    }
    QString sheet;
    sheet = "border-image: url(" + icon + ");";
    m_lb_icon->setStyleSheet(sheet);
    m_lb_icon->setPixmap(m_icon);
    vlay->setContentsMargins(0,0,0,0);
    vlay->setSpacing(5);

    vlay->addWidget(m_lb_icon,0,Qt::AlignHCenter);

    if  ( type == HAVE_TEXT )
    {
        m_lb_txt = new QLabel(this);
        m_lb_txt->setAttribute(Qt::WA_TranslucentBackground);
        m_lb_txt->setStyleSheet("color: rgb(255, 255, 255);");
        m_lb_txt->setWordWrap(true);

        vlay->addWidget(m_lb_txt,0,Qt::AlignHCenter);
        setMinimumSize(80,65);
    }else
        setMinimumSize(40,40);

    setLayout(vlay);

    setAttribute(Qt::WA_TranslucentBackground);

    m_color = QColor(0,0,0,0);

}

DeskIcon::~DeskIcon()
{

}

void DeskIcon::setTextStyle(QString style)
{
    m_lb_txt->setStyleSheet(style);
}

void DeskIcon::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    QPainterPath path;
    path.addRoundRect(rect(),20);
    painter.fillPath(path,QBrush(m_color));
}

void DeskIcon::enterEvent(QEvent *evt)
{
    m_color = QColor(255, 37, 246,40);

    setCursor(Qt::PointingHandCursor);
    update();

}
void DeskIcon::leaveEvent(QEvent *evt)
{
    m_color = QColor(0,0,0,0);

    setCursor(Qt::ArrowCursor);
    update();
}

void DeskIcon::mouseDoubleClickEvent(QMouseEvent *evt)
{
    if ( m_type == HAVE_TEXT)
    {
        QString txt = m_lb_txt->text();
        emit dbclick(txt);
        ShellExecuteA(this->winId(),"open",m_path.toLocal8Bit().data(),NULL,NULL,SW_SHOWNORMAL);
    }
}

void DeskIcon::mousePressEvent(QMouseEvent *evt)
{
    if ( Qt::LeftButton == evt->button())
    {

        m_pressed = true;
        m_movePoint = evt->globalPos() - pos();
    }
}

void DeskIcon::mouseReleaseEvent(QMouseEvent *evt)
{
    m_pressed = false;
    emit click(m_txt);
    emit clicked();
}

void DeskIcon::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_pressed)
    {
        move(evt->globalPos() - m_movePoint);
    }
}
