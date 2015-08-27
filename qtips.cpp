#include "qtips.h"
#include "qtiptxt.h"


#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QMouseEvent>
#include <QScrollArea>

QTips::QTips(QWidget *parent) :
    FramelessWin(parent)
{
    //resize(200,200);
    setWindowOpacity(0.8);
    setResizable(false);
    SetupUI();
    _preText = NULL;

    //for ( int i = 0 ; i < 3; ++i)
//    addNotifyText(QString::fromLocal8Bit("用户登录XMPP Server后首先向负载均衡组件"
//                                         "请求目前可用的负载较轻的组件，负载均衡组件"
//                                         "通过查询各组件的真实负载情况，返回负载最轻的"
//                                         "组件的域名交给客户端。此后，客户端进行的实际业"
//                                         "务请求均提交给该组件。详细流程如下图"));
}

//布置提示便签的UI
void QTips::SetupUI()
{

//    _preBtn = new IconButton(this,":/ui/btn_normal.png",":/ui/btn_highlight.png"
//                             ,":/ui/btn_down.png");
//    _nextBtn = new IconButton(this,":/ui/btn_normal.png",":/ui/btn_highlight.png"
//                             ,":/ui/btn_down.png");

//    _preBtn->SetButtonText(QString::fromLocal8Bit("上一条"));
//    _nextBtn->SetButtonText(QString::fromLocal8Bit("下一条"));

    this->setAttribute(Qt::WA_TranslucentBackground);
    txtWidget = new QWidget(this);
    txtWidget->setObjectName("txtWidget");
    txtWidget->setMaximumSize(220,180);
    txtWidget->setMinimumSize(220,180);
    //txtWidget->setStyleSheet("QWidget#txtWidget{background-color: rgb(205, 236, 211);}");

    QWidget *navw = new QWidget(this);
    _preBtn = new IconButton(navw,":/ui/pre.png",":/ui/pre-high.png",":/ui/pre-down.png");
    _nextBtn = new IconButton(navw,":/ui/next.png",":/ui/next-high.png",":/ui/next-down.png");

    QHBoxLayout *navlay = new QHBoxLayout(navw);

    navlay->addWidget(_preBtn);
    navlay->addStretch();
    navlay->addWidget(_nextBtn);

//    QScrollArea *scroll = new QScrollArea(this);
//    scroll->setStyleSheet("background-color: rgb(205, 236, 211);");
//    scroll->setWidget(txtWidget);
//    scroll->setAttribute(Qt::WA_TranslucentBackground);
//    scroll->setFrameShadow(QFrame::Plain);

    _vlay = new QVBoxLayout(txtWidget);

    _vlay->setSpacing(10);
    _vlay->addStretch();

    //txtWidget->resize(400,150);

//    QWidget *titlewid = new QWidget(this);
//    titlewid->setStyleSheet("background-color: rgb(205, 236, 211);");
    QWidget *tw = new QWidget(this);
    _lbtitle = new QLabel(tw);
//    _lbtitle->setText(QString::fromLocal8Bit("工资上报通知"));
    IconButton *closebtn = new IconButton(tw,":/ui/btn_close_normal.png",":/ui/btn_close_highlight.png"
                                          ,":/ui/btn_close_down.png");

    connect(closebtn,SIGNAL(clicked()),this,SLOT(click_close()));
    _lbtitle->setAttribute(Qt::WA_TranslucentBackground);
    _lbtitle->setStyleSheet("font: 75 16pt \"Times New Roman\";");

    _lbtitle->setMaximumHeight(50);

    QHBoxLayout *h = new QHBoxLayout(tw);
    h->addStretch();
    h->addWidget(_lbtitle);
    h->addStretch();
    h->addWidget(closebtn,0,Qt::AlignRight);
    h->setMargin(0);

    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->setContentsMargins(0,5,0,0);
    vlay->setSpacing(0);

    vlay->addWidget(tw,0,Qt::AlignTop);
    vlay->addWidget(navw);
    //vlay->addWidget(_lbtitle,0,Qt::AlignHCenter);
    vlay->addWidget(txtWidget);

}

QTips::~QTips()
{

}

void QTips::removeTips(QWidget *tip)
{
    _vlay->removeWidget(tip);
}

void QTips::addNotifyText(QString txt)
{
//    QLabel *lb = new QLabel(this);
//    lb->setAttribute(Qt::WA_TranslucentBackground);
//    lb->setText(txt);

    if ( NULL != _preText )
    {
        removeTips(_preText);
        delete _preText;
        _preText = NULL;
    }
    QTipTxt *lb = new QTipTxt(txtWidget);
    lb->setText(txt);
    _vlay->insertWidget(0,lb);

    _preText = lb;

}

void QTips::click_close()
{
    close();
}

void QTips::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing,true);

    QStyleOption opt;

    opt.init(this);

    QStyle *sty = style();

    sty->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    QBrush brush(QColor(205, 236, 111,50));
    painter.setBrush(brush);

    painter.fillRect(rect(),brush);

}

//void QTips::mousePressEvent(QMouseEvent *evt)
//{
//    if ( evt->button() == Qt::LeftButton)
//    {
//        _movepoint = evt->pos();
//        _pressed = true;
//    }
//}
//void QTips::mouseReleaseEvent(QMouseEvent *evt)
//{
//    _pressed = false;
//}

//void QTips::mouseMoveEvent(QMouseEvent *evt)
//{
//    if ( _pressed )
//    {
//        move( evt->globalPos() - _movepoint);
//    }
//}
