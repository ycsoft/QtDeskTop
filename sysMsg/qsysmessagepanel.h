#ifndef QSYSMESSAGEPANEL_H
#define QSYSMESSAGEPANEL_H

#include <QWidget>
#include <QGridLayout>

#include "uiframe/qnoframewin.h"

class QSysMessagePanel : public QWidget
{
    Q_OBJECT
public:
    explicit QSysMessagePanel(QWidget *parent = 0);
    ~QSysMessagePanel(){}

    void     anim_Show();
    void     anim_Hide();

    QGridLayout *getLayout()
    {
        return m_lay;
    }

    void    addMessage(const QString &from, const QString &msg);
protected:
    void    enterEvent(QEvent *evt);
    void    mousePressEvent(QMouseEvent *evt);
    void    mouseMoveEvent(QMouseEvent *evt);
    void    mouseReleaseEvent(QMouseEvent *evt);

    void    paintEvent(QPaintEvent *evt);
    void    initUI();
signals:

public slots:

private:
    int     m_currow;
    QGridLayout     *m_lay;
    bool    m_isPressed;
    QPoint  m_movePoint;
};

#endif // QSYSMESSAGEPANEL_H
