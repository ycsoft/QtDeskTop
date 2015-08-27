#include "qtodowidget.h"
#include "utils/defines.h"

#include <QMouseEvent>

QToDoWidget::QToDoWidget(QWidget *parent) : QPureColorButton(parent)
{

    setButtonText(LOCAL("事项管理"));
    setColors(QColor(0,0,100),QColor(0,200,200)
                              ,QColor(0,100,100),QColor(0,150,150));
    setTextStyle("font: 75 14pt \"Aharoni\";"
                 "color: rgb(248, 248, 248);");
}


void QToDoWidget::mousePressEvent(QMouseEvent *evt)
{
    QPureColorButton::mousePressEvent(evt);
    if ( evt->button() == Qt::LeftButton )
    {
        m_pressed = true;
        m_pressPoint = evt->globalPos() - pos();
    }
}
void QToDoWidget::mouseReleaseEvent(QMouseEvent *evt)
{
    QPureColorButton::mouseReleaseEvent(evt);
    m_pressed = false;
}

void QToDoWidget::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_pressed )
    {
        move(evt->globalPos() - m_pressPoint);
    }
}

void QToDoWidget::enterEvent(QEvent *evt)
{
    QPureColorButton::enterEvent(evt);
}
void QToDoWidget::resizeEvent(QResizeEvent *evt)
{
    QSize sz = evt->size();

}
