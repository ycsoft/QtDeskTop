#ifndef NAVBUTTON_H
#define NAVBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QMenu>

class NavButton : public QPushButton
{
    Q_OBJECT
public:
    explicit NavButton(QWidget *parent = 0);
    enum Status{ Normal, High, Down,Selected};

    NavButton(QWidget *parent,QString icon, QString txt);

    void setStatus( Status st );

    void setButtonText(QString txt);

    void setTextStyle(QString style);

    //设置按钮菜单
    void setMenu(QMenu *menu)
    {
        m_menu = menu;
    }



signals:

public slots:

private:

    void            enterEvent(QEvent *evt);
    void            leaveEvent(QEvent *evt);

    void            mousePressEvent(QMouseEvent *evt);
    void            mouseReleaseEvent(QMouseEvent *evt);

    void            paintEvent(QPaintEvent *evt);

private:
    QList<QPixmap>  m_pic_list;

    QPixmap         *m_current_pic;

    QString         m_icon_path;
    QString         m_txt;

    QLabel          *lb_pic;
    QLabel          *lb_txt;

    Status          m_status;

    QMenu           *m_menu;
};

#endif // NAVBUTTON_H
