#include "qpurecolorbutton.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QVBoxLayout>

QPureColorButton::QPureColorButton(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    m_pressed = false;
    m_entered = false;
    setMinimumHeight(40);
    //
    m_lbtitle = new QLabel(this);
    m_lbtitle->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addWidget(m_lbtitle,0,Qt::AlignHCenter | Qt::AlignVCenter);
    m_lbtitle->setText("PushButton");
    m_lbtitle->setWordWrap(true);
    setColors(  QColor(255, 255, 255),
                QColor(85, 160, 127),
                QColor(85, 160, 127),
                QColor(255,255,255));
}


void QPureColorButton::enterEvent(QEvent *)
{
    m_currentColor = m_enterColor;
    m_entered = true;
    update();
}

void QPureColorButton::leaveEvent(QEvent *)
{
    m_currentColor = m_leaveColor;
    m_entered = false;
    update();
}

void QPureColorButton::mousePressEvent(QMouseEvent *evt)
{
    if( evt ->button() == Qt::LeftButton )
    {
        m_pressed = true;
    }
    m_currentColor = m_pressColor;
    emit clicked();
    emit clicked(m_index);
    update();
}
void QPureColorButton::mouseReleaseEvent(QMouseEvent *)
{
    m_pressed = false;
    m_currentColor = m_releaseColor;
    update();

}

void QPureColorButton::paintEvent(QPaintEvent *)
{
    QPainter    p(this);
    QBrush      brush( m_currentColor );
    QPen        pen( Qt::NoPen );
    QStyleOption    op;
    op.init(this);

    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);

    p.setBrush(brush);
    p.setPen(pen);
    p.drawRect(rect());
    p.setPen(Qt::black);
}

void QPureColorButton::setColors(const QColor &pres, const QColor &release, const QColor &enter, const QColor &leave)
{
    m_pressColor = pres;
    m_releaseColor = release;
    m_enterColor = enter;
    m_leaveColor = leave;
    m_currentColor = m_leaveColor;
    update();
}
