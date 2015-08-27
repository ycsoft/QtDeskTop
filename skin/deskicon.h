#ifndef DESKICON_H
#define DESKICON_H

#include <QPushButton>
#include <QLabel>
#include "skin/framelesswin.h"

class DeskIcon : public QPushButton
{
    Q_OBJECT
public:

    enum Type{ HAVE_TEXT, NO_TEXT,PATH_NAME};
    /**
     * @brief DeskIcon
     * @param parent
     * @param icon
     * 构造适合桌面显示的图标
     */

    explicit DeskIcon(QWidget *parent = 0,QString icon= "",int type = HAVE_TEXT);

    void SetupUI()
    {

    }

    ~DeskIcon();

    void setTextStyle(QString style);
    void   setIconText(QString txt)
    {
        m_txt = txt;
        if (m_type == HAVE_TEXT)
            m_lb_txt->setText( txt);
    }

    QString & getText()
    {
        return m_txt;
    }

    void  setIcon(QString icon)
    {
        m_lb_icon->setPixmap(QPixmap(icon).scaled(48,48));
    }

    void setIcon(QPixmap &icon)
    {
        m_lb_icon->setPixmap(icon.scaled(48,48));
    }
    void setAppPath(QString path)
    {
        m_path = path;
    }
    void scaled( int w,int h)
    {
        m_icon = m_icon.scaled(w,h);
    }

    /**
     * @brief paintEvent
     * @param evt
     */
    virtual void paintEvent(QPaintEvent *evt);

    void enterEvent(QEvent *evt);
    void leaveEvent(QEvent *evt);

    void mouseDoubleClickEvent(QMouseEvent *evt);

    void mousePressEvent(QMouseEvent *evt);

    void mouseReleaseEvent(QMouseEvent *evt);

    void mouseMoveEvent(QMouseEvent *evt);


signals:
    void dbclick(QString);
    void click(QString);

public slots:

private:
    QLabel  *m_lb_icon;
    QLabel  *m_lb_txt;
    QPixmap m_icon;

    QColor  m_color;
    int     m_type;
    QString m_txt;
    QString m_path;

    bool        m_pressed;
    QPoint      m_movePoint;
};

#endif // DESKICON_H
