#ifndef QHTMLDOCK_H
#define QHTMLDOCK_H


#include "utils/qhfwebview.h"

#include <QWidget>
#include <QPaintEvent>


/**
 * @brief The QHtmlDock class
 * 使用HTML语言构建的DOCK
 */
class QHtmlDock : public QWidget
{
    Q_OBJECT
public:
    explicit QHtmlDock(QWidget *parent = 0);

protected:
    void    initUI();
    void    paintEvent(QPaintEvent *);


    void mousePressEvent(QMouseEvent *evt);

    void mouseReleaseEvent(QMouseEvent *evt);

    void mouseMoveEvent(QMouseEvent *evt);
signals:

public slots:

private:
    QHFWebView      *m_web;

    bool        m_pressed;
    QPoint      m_movePoint;
    int         m_appCount;
};

#endif // QHTMLDOCK_H
