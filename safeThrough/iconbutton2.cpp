
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QPainter>


#include "iconbutton2.h"



IconButton2::IconButton2(QWidget *parent,QString iconnormal,QString iconHigh,QString icondown)
{
    QPixmap pix_0(iconnormal);
    QPixmap pix_1(iconHigh);
    QPixmap pix_2(icondown);
    m_icon_list.append(pix_0);
    m_icon_list.append(pix_1);
    m_icon_list.append(pix_2);
    if (!iconnormal.isEmpty())
    {
        m_cur_icon = pix_0;
        setFixedSize(m_cur_icon.size());
    }
    setAttribute(Qt::WA_TranslucentBackground);
}

//设置按钮文本
void IconButton2::SetButtonText(QString txt)
{
    m_txt = txt;
    if ( !txt.isEmpty() )
    {
        m_txt_lb->setText(txt);
    }
}

//设置文本风格
void IconButton2::SetTextStyle(QString style)
{
    m_txt_lb->setStyleSheet(style);
}

//添加文本标签
void IconButton2::AddTxtLabel()
{
    m_txt_lb = new QLabel(this);
    m_txt_lb->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(m_txt_lb);
    this->setLayout(lay);
}

//设置按钮图标
void IconButton2::SetButtonIcon(QString iconpath)
{
    if ( !iconpath.isEmpty())
        m_cur_icon = QPixmap(iconpath);
}

//设置按钮状态
void IconButton2::SetStatus(int status)
{
    m_status = status;
    switch(status)
    {
        case BUTTON_ENTER:
        {
            m_cur_icon = m_icon_list[1];
            break;
        }
        case BUTTON_PRESSED:
        {
            m_cur_icon = m_icon_list[2];
            break;
        }
        case BUTTON_LEAVE:
        {
            m_cur_icon = m_icon_list[0];
            break;
        }
    }
}

void IconButton2::enterEvent(QEvent *evt)
{
    SetStatus(BUTTON_ENTER);
}

void IconButton2::leaveEvent(QEvent *evt)
{
    SetStatus(BUTTON_LEAVE);
}

void IconButton2::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),m_cur_icon);
}

void IconButton2::mousePressEvent(QMouseEvent *evt)
{
    if ( evt->button() == Qt::LeftButton )
    {
        SetStatus(BUTTON_PRESSED);
        emit clicked();
    }
}
void IconButton2::mouseReleaseEvent(QMouseEvent *evt)
{
    SetStatus(BUTTON_LEAVE);
}
