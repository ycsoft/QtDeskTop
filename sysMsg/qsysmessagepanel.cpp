#include "qsysmessagepanel.h"

#include "winFactory/qwinfactory.h"
#include "utils/qapputils.h"
#include "uiframe/qhfscroll.h"

#include <QSpacerItem>
#include <QPainter>
#include <QStyle>
#include <QScrollArea>
#include <QPropertyAnimation>
QSysMessagePanel::QSysMessagePanel(QWidget *parent) : QWidget(parent)
{
    m_currow = 0;
    initUI();

    setMinimumHeight(QAppUtils::ref().getScreenHei() - QAppUtils::ref().getTaskBarHeight());
    setMaximumHeight(QAppUtils::ref().getScreenHei() - QAppUtils::ref().getTaskBarHeight());
    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
    addMessage(LOCAL("通知"),LOCAL("下午大扫除，请大家注意，不要早退，不要迟到哦...........一定要记住哦亲"));
    addMessage(LOCAL("国土资源部公告"),LOCAL("为方便申请人和社会公众及时了解申请项目的受理、办理进展和结果，"
                                      "自2015年8月1日起，国土资源部在部门户网站开通行政审批信息网上公开查询服务平台"));
    addMessage(LOCAL("关于2015年记账式附息(十一期)国债"
                     "第二次续发行工作有关事宜的通知"),LOCAL("2015-2017年记账式国债承销团成员，中央国债登记结算有限责任公司、中国证券登记结算有限责任公司、中国外汇交易中心、上海证券交易所、深圳证券交易所"));

    m_isPressed = false;
}

void QSysMessagePanel::addMessage(const QString &from, const QString &msg)
{
    int width = QAppUtils::ref().getScreenWid();
    QMessageWidgets *msgWidget =
            dynamic_cast<QMessageWidgets*> (QWinFactory::ref().createWindow(QWinFactory::MsgWidget,this));

    msgWidget->setMinimumWidth(width/4.3);
    msgWidget->setWindowTitle(from);
    msgWidget->setMessage(msg);
    msgWidget->setAttribute(Qt::WA_TranslucentBackground);
    getLayout()->addWidget(msgWidget,m_currow++,0,1,1,Qt::AlignHCenter);
}

void QSysMessagePanel::initUI()
{

    QWidget     *headw = new QWidget(this);
    QLabel      *lbtitle = new QLabel(headw);
    IconButton  *closeB = QAppUtils::ref().getCloseIconBtn(headw);
    QHBoxLayout *headLay = new QHBoxLayout(headw);
    QWidget     *center = new QWidget(this);
    QWidget     *msgWid = new QWidget(center);
    QHFScroll *scroll = new QHFScroll(this);
    QVBoxLayout *vlay = new QVBoxLayout(this);
    QVBoxLayout *vlayMsg = new QVBoxLayout(center);
    int         width,height;


//    center->setAttribute(Qt::WA_TranslucentBackground);

    vlay->setContentsMargins(0,0,0,0);

    //中部消息区
    vlayMsg->addWidget(msgWid);
    vlayMsg->addStretch();

    QAppUtils::ref().getScreenSize(width,height);
    center->setMinimumSize(width/4.1,height/1.3);
    scroll->setBackgroundRole(QPalette::NoRole);
    scroll->setWidget(center);
    scroll->setAttribute(Qt::WA_TranslucentBackground);
    scroll->setMinimumSize(width/4,height/1.2);
    scroll->setWindowFlags(Qt::FramelessWindowHint);
    scroll->setFrameShadow( QFrame::Plain );

    lbtitle->setStyleSheet("font: 75 14pt \"Times New Roman\";");
    lbtitle ->setText(LOCAL("系统通知"));
    headLay->addStretch();
    headLay->addWidget(lbtitle);
    headLay->addStretch();
    headLay->addWidget(closeB);
    connect(closeB,SIGNAL(clicked()),this,SLOT(close()));
    m_lay = new QGridLayout(msgWid);
    m_lay->setContentsMargins(0,0,0,0);
    vlay->addWidget(headw);
    vlay->addWidget(scroll);
    vlay->addStretch();
}

void QSysMessagePanel::enterEvent(QEvent *evt)
{
    setAttribute(Qt::WA_PaintOnScreen);
}

void QSysMessagePanel::paintEvent(QPaintEvent *evt)
{
    QPainter p(this);
    QStyleOption op;
    op.init(this);

    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);

//    p.fillRect(rect(),QColor(100,100,20,0));
}


void QSysMessagePanel::mousePressEvent(QMouseEvent *evt)
{
    if ( evt->button() == Qt::LeftButton )
    {
        m_isPressed = true;
        m_movePoint = evt->globalPos()- pos();
    }else
    {
        m_isPressed = false;
    }
}
void QSysMessagePanel::mouseReleaseEvent(QMouseEvent *evt)
{
    m_isPressed = false;
}
void QSysMessagePanel::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_isPressed )
    {
        move(evt->globalPos() - m_movePoint);
    }
}
void QSysMessagePanel::anim_Show()
{
    int wid,hei;
    setVisible(true);
    QPropertyAnimation *anim = new QPropertyAnimation(this,"pos");

    QAppUtils::ref().getScreenSize(wid,hei);

    anim->setStartValue(QPoint(wid,0));
    anim->setEndValue(QPoint(wid-width(),0));
    anim->start();
}
void QSysMessagePanel::anim_Hide()
{
    int wid,hei;
    setVisible(true);
    QPropertyAnimation *anim = new QPropertyAnimation(this,"pos");

    QAppUtils::ref().getScreenSize(wid,hei);

    anim->setEndValue(QPoint(wid,0));
    anim->setStartValue(QPoint(wid-width(),0));
    anim->start();
    connect(anim,SIGNAL(finished()),this,SLOT(hide()));
}

