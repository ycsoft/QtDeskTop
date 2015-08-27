#ifndef QPROPERTY_H
#define QPROPERTY_H

#include <QDialog>
#include <QLabel>


#include "skin/framelesswin.h"
#include "skin/iconbutton.h"

class QProperty : public FramelessWin
{
    Q_OBJECT
public:
    explicit QProperty(QWidget *parent = 0);

    void SetupUI();

    QString  m_desktop_style;

    //根据图片路径构建设置壁纸的style表达式
    static QString deskStyleFromPath(QString picpath);

signals:

    void    signal_change(QString);
public slots:

    void    slot_click();

private:
    QLabel      *m_lb_pic;


};

#endif // QPROPERTY_H
