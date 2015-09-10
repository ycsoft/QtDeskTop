#ifndef FRAMELESSWIN2_H
#define FRAMELESSWIN2_H

#include <QDialog>
#include <QPoint>

class FramelessWin2 : public QDialog
{
    Q_OBJECT
public:
    enum Direct {
                 UP,DOWN,LEFT,
                 RIGHT,LEFTTOP,
                 LEFTDOWN,RIGHTTOP,
                 RIGHTDOWN,UNKOWN
                };
    explicit FramelessWin2(QWidget *parent = 0,QString s="");
    virtual ~FramelessWin2();


    void SetInfo(QString s) { m_info = s;}
    void GetMoveDirect(QPoint cursorPoint);
    void changeSize(QRect &move,QPoint pos);
    //重载事件
    void mousePressEvent(QMouseEvent *evt);
    void mouseReleaseEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void paintEvent(QPaintEvent *evt);


signals:

public slots:
    void        okClick();
private:
    //构建右上角按钮
    void        InitTop();

    int         m_direct;
    int         m_padding;
    bool        m_pressed;
    QPoint      m_movePoint;
    QString     m_info;

};

#endif // FRAMELESSWIN_H
