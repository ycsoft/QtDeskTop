#ifndef QTODOWIDGET_H
#define QTODOWIDGET_H

#include "uiframe/qpurecolorbutton.h"

#include<screenOper/qscreenshort.h>
#include <QWidget>

class QToDoWidget : public QPureColorButton
{
    Q_OBJECT
public:
    explicit QToDoWidget(QWidget *parent = 0);
    ~QToDoWidget() {}

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);
    void enterEvent(QEvent*);

signals:

public slots:
private:
    bool            m_pressed;
    QPoint          m_pressPoint;

};

#endif // QTODOWIDGET_H
