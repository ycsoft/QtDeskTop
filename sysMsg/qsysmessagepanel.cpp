#include "qsysmessagepanel.h"

#include "winFactory/qwinfactory.h"
#include "utils/qapputils.h"

#include <QSpacerItem>
#include <QScrollArea>

QSysMessagePanel::QSysMessagePanel(QWidget *parent) : QWidget(parent)
{
    m_currow = 0;
    resize(200,600);
    initUI();
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    addMessage(LOCAL("通知"),LOCAL("下午大扫除，请大家注意，不要早退，不要迟到哦...........一定要记住哦亲"));
    addMessage(LOCAL("国土资源部公告"),LOCAL("为方便申请人和社会公众及时了解申请项目的受理、办理进展和结果，"
                                      "自2015年8月1日起，国土资源部在部门户网站开通行政审批信息网上公开查询服务平台"));
    addMessage(LOCAL("关于2015年记账式附息(十一期)国债"
                     "第二次续发行工作有关事宜的通知"),LOCAL("2015-2017年记账式国债承销团成员，中央国债登记结算有限责任公司、中国证券登记结算有限责任公司、中国外汇交易中心、上海证券交易所、深圳证券交易所"));
}

void QSysMessagePanel::addMessage(const QString &from, const QString &msg)
{
    int width = QAppUtils::ref().getScreenWid();
    QMessageWidgets *msgWidget =
            dynamic_cast<QMessageWidgets*> (QWinFactory::ref().createWindow(QWinFactory::MsgWidget,this));

    msgWidget->setMinimumWidth(width/4.2);
    msgWidget->setWindowTitle(from);
    msgWidget->setMessage(msg);
    msgWidget->setAttribute(Qt::WA_TranslucentBackground);
    getLayout()->addWidget(msgWidget,m_currow++,0,1,1,Qt::AlignHCenter);
}

void QSysMessagePanel::initUI()
{
    QWidget     *headw = new QWidget(this);
    IconButton  *closeB = QAppUtils::ref().getCloseIconBtn(headw);
    QHBoxLayout *headLay = new QHBoxLayout(headw);
    QWidget     *center = new QWidget(this);
    QWidget     *msgWid = new QWidget(center);
    QScrollArea *scroll = new QScrollArea(this);
    QVBoxLayout *vlay = new QVBoxLayout(this);
    QVBoxLayout *vlayMsg = new QVBoxLayout(center);
    int         width,height;


    vlay->setContentsMargins(0,0,0,0);
    vlayMsg->addWidget(msgWid);
    vlayMsg->addStretch();

    QAppUtils::ref().getScreenSize(width,height);
    center->setMinimumSize(width/4.1,height/1.3);
    scroll->setBackgroundRole(QPalette::Dark);
    scroll->setWidget(center);
    scroll->setMinimumSize(width/4,height/1.2);

    headLay->addStretch();
    headLay->addWidget(closeB);
    connect(closeB,SIGNAL(clicked()),this,SLOT(close()));
    m_lay = new QGridLayout(msgWid);
    m_lay->setContentsMargins(0,0,0,0);
    vlay->addWidget(headw);
    vlay->addWidget(scroll);
    vlay->addStretch();
}
