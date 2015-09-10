
#include <QRect>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include <math.h>
#include <QHBoxLayout>
#include <QApplication>
#include <QLabel>



#include "framelesswin2.h"
#include "iconbutton2.h"
#include "session.h"

#ifndef LOCAL(x)
#define LOCAL(x)  QString::fromLocal8Bit(x)
#endif


FramelessWin2::FramelessWin2(QWidget *parent,QString s) :
    QDialog(parent),m_info(s)
{
    setWindowFlags(Qt::FramelessWindowHint);
    m_movePoint = QPoint(0,0);
    m_pressed = false;
    setAttribute(Qt::WA_TranslucentBackground);
    m_padding = 5;
    m_direct = UNKOWN;
    setMouseTracking(true);
    InitTop();
    resize(310,450);
}

FramelessWin2::~FramelessWin2()
{

}

void FramelessWin2::GetMoveDirect(QPoint cursorPoint)
{
QRect rect = this->rect();
QPoint tl = mapToGlobal(rect.topLeft());
QPoint rb = mapToGlobal(rect.bottomRight());
int x = cursorPoint.x();
int y = cursorPoint.y();
//左上角
if( x-m_padding <= tl.x() && x >= tl.x() && y - m_padding <= tl.y() && y >= tl.y())
{
    m_direct = FramelessWin2::LEFTTOP;
    setCursor(Qt::SizeFDiagCursor);
}
//左下角
else if (x - m_padding <= tl.x() && x > tl.x() && y - m_padding <= rb.y() && y >= rb.y())
{
    m_direct = LEFTDOWN;
    setCursor(Qt::SizeBDiagCursor);
}
//左边
else if (x <= tl.x() + m_padding && x >= tl.x())
{
    m_direct = LEFT;
    setCursor(Qt::SizeHorCursor);
}
//右上角
else if (x <= rb.x() && x + m_padding >= rb.x() && y >= tl.y() && y - m_padding <= tl.y())
{
    m_direct = RIGHTTOP;
    setCursor(Qt::SizeBDiagCursor);
}
//右下角
else if (x <= rb.x() && x + m_padding >= rb.x() && y <= rb.y() && y + m_padding >= rb.y())
{
    m_direct = RIGHTDOWN;
    setCursor(Qt::SizeFDiagCursor);
}
//右边
else if (x <= rb.x() && x + m_padding >= rb.x())
{

    m_direct = RIGHT;
    setCursor(Qt::SizeHorCursor);
}
//上
else if (y > tl.y() && y < tl.y()+m_padding)
{
    m_direct = UP;
    setCursor(Qt::SizeVerCursor);
}
else if (y <= rb.y() && y +  m_padding >= rb.y())
{
    m_direct = DOWN;
    setCursor(Qt::SizeVerCursor);
}
else
{
    m_direct = UNKOWN;
    setCursor(Qt::ArrowCursor);
}
}

void FramelessWin2::changeSize(QRect &move, QPoint pos)
{
    QRect cur = rect();
    QPoint tl = mapToGlobal(cur.topLeft());
    QPoint rb = mapToGlobal(cur.bottomRight());

    if (m_direct == LEFT)
        move.setX(pos.x());
    else if (m_direct == RIGHT)
        move.setWidth(pos.x() - tl.x());
    else if (m_direct == LEFTTOP){
        move.setX(pos.x());
        move.setY(pos.y());
    }
    else if (m_direct == RIGHTTOP){
        move.setWidth(pos.x() - tl.x());
        move.setY(pos.y());
    }
    else if (m_direct == LEFTDOWN){
        move.setHeight(pos.y()- tl.y());
        move.setX(pos.x());}
    else if (m_direct == RIGHTDOWN){
        move.setWidth(pos.x()-tl.x());
        move.setHeight(pos.y() - tl.y());}
    else if (m_direct == UP)
        move.setY(pos.y());
    else if (m_direct == DOWN)
        move.setHeight(pos.y() - tl.y());

}
void FramelessWin2::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button() != Qt::LeftButton)
    {
        m_pressed = false;
    }
    else
    {
        m_pressed = true;
        m_movePoint = evt->globalPos()-pos();
    }
}
void FramelessWin2::mouseReleaseEvent(QMouseEvent *evt)
{
    if (evt->button() != Qt::LeftButton)
    {
        m_pressed = true;
    }else
    {
        m_pressed = false;
    }
}
void FramelessWin2::mouseMoveEvent(QMouseEvent *evt)
{
    QPoint globalPos = evt->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint tb  = mapToGlobal(rect.bottomRight());
    QRect rmove(tl,tb);
    if ( m_pressed )
    {
        if (m_direct == UNKOWN )
        {
            move(evt->globalPos()-m_movePoint);
        }
        else
        {
            changeSize(rmove,globalPos);
            setGeometry(rmove);
        }
    }
    else
    {
        GetMoveDirect(globalPos);
    }
}
void FramelessWin2::paintEvent(QPaintEvent *evt)
{
    /*
    添加阴影效果
    :param args:
    :param kwargs:
    :return:
    */
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    QStyle *style = this->style();
    style->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10,10,width()-20,height()-20);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillPath(path,QBrush(Qt::white));
    QColor color(0,0,0,50);
    int i = 0;
    //for i in xrange(10):
    for (i = 0 ; i < 10; i++)
    {
        QPainterPath path2;
        path2.setFillRule(Qt::WindingFill);
        path2.addRect(10-i,10-i,width()-(10-i)*2,height()-(10-i)*2);
        color.setAlpha(150 - sqrt((float)i)*50);
        painter.setPen(color);
        painter.drawPath(path2);
    }
    QPixmap back("./UI/skin.png");
    i = 0;
    painter.drawPixmap(10-i,10-i,width()-(10-i)*2,height()-(10-i)*2,back);

}
void FramelessWin2::okClick()
{
    Session::Instance()->SetConfirmed(true);
    accept();
}

//界面
void FramelessWin2::InitTop()
{
    QWidget  *topSkin = new QWidget(this);
    topSkin->setMinimumHeight(160);
    //IconButton *setb = new IconButton(this,":/UI/btn_set_normal.png",":/UI/btn_set_hover.png",":/UI/btn_set_press.png");
    //IconButton *minb = new IconButton(this,":/UI/btn_mini_normal.png",":/UI/btn_mini_highlight.png",":/UI/btn_mini_down.png");
    IconButton2 *closeb = new IconButton2(this,":/UI/btn_close_normal.png",":/UI/btn_close_highlight.png",":/UI/btn_close_down.png");
    topSkin->setStyleSheet("border-image: url(:/UI/background.png);");

    connect(closeb,SIGNAL(clicked()),this,SLOT(close()));
    QHBoxLayout *topLay = new QHBoxLayout();
    topLay->setMargin(0);
    topLay->addStretch();
    //topLay->addWidget(setb,0,Qt::AlignRight | Qt::AlignTop);
    //topLay->addWidget(minb,0,Qt::AlignRight | Qt::AlignTop);
    topLay->addWidget(closeb,0,Qt::AlignRight | Qt::AlignTop);
    topSkin ->setLayout(topLay);

    QLabel *lb = new QLabel(this);
    QLabel *title = new QLabel(this);
    title->setText(LOCAL("应用程序登录确认"));
    lb->setText(m_info);
    lb->setStyleSheet("font: 75 11pt 'Times New Roman';");
    title->setStyleSheet("font: 75 11pt 'Times New Roman';");

    IconButton2 *okButton = new IconButton2(this,":/UI/button_login_normal.png",":/UI/button_login_hover.png",
                                             ":/UI/button_login_down.png");

    connect(okButton,SIGNAL(clicked()),this,SLOT(okClick()));
    okButton->AddTxtLabel();
    okButton->SetButtonText(QString::fromLocal8Bit("授权登录"));

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->addWidget(topSkin);
    mainLay->addWidget(title,0,Qt::AlignHCenter);
    mainLay->addStretch();
    mainLay->addWidget(lb,0,Qt::AlignHCenter);
    mainLay->addWidget(okButton,0,Qt::AlignHCenter);
    mainLay->addStretch();

}

