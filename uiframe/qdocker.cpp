#include "qdocker.h"
#include "utils/defines.h"
#include "skin/deskicon.h"
#include "utils/qapputils.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QLabel>
#include <QMouseEvent>

QDocker::QDocker(QWidget *parent) : QWidget(parent)
{
    m_web = new QWebView(this);

    //m_web->setWindowFlags(Qt::FramelessWindowHint);
    m_appCount = 0;
    initUI();
    addApp((LOCAL("xjb/公务卡系统3.4.0/GwCard.exe")),LOCAL("公务卡"));
    addApp(LOCAL("xjb/县区财政预算执行系统系统管理3.4.0/jy.exe"),LOCAL("系统管理"));
    addApp((LOCAL("xjb/县区财政预算总会计账务系统3.4.0.0/Account.exe")),LOCAL("会计账务"));
    addApp((LOCAL("xjb/县区行政事业单位账务系统3.4.0.0/DwAccount.exe")),LOCAL("单位账务"));
    addApp((LOCAL("xjb/县区预算执行动态监控及综合查询系统 3.2.0.0/GkQuery.exe")),LOCAL("动态监控"));
    addApp((LOCAL("xjb/县区预算执行系统3.4.0/GkCounty.exe")),LOCAL("预算执行"));
    addApp((LOCAL("xjb/银行支付系统3.4.0/BankClient.exe")),LOCAL("银行支付"));
}

void QDocker::initUI()
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);

    resize(DOCK_WID,DOCK_HEI);
    QLabel *lb = new QLabel(this);
    lb->setPixmap(QPixmap("html/img/docker.png"));
    lay->addWidget(lb);
    //m_web->load(QUrl("html/dock.html"));
}
void QDocker::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);

    QStyleOption opt;

    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);
//    painter.fillRect(rect(),QColor(0,0,0,30));
}
void QDocker::mousePressEvent(QMouseEvent *evt)
{
    if ( Qt::LeftButton == evt->button())
    {

        m_pressed = true;
        m_movePoint = evt->globalPos() - pos();
    }
}

void QDocker::mouseReleaseEvent(QMouseEvent *evt)
{
    m_pressed = false;
}

void QDocker::mouseMoveEvent(QMouseEvent *evt)
{
    if ( m_pressed)
    {
        move(evt->globalPos() - m_movePoint);
    }
}
void QDocker::addApp(QPixmap &pix, QString &title, QString &path)
{
    int padding = 20;
    int iconwid = 40;
    int x = (m_appCount++) * (iconwid + padding) + padding;
    int y = 10;
    DeskIcon *dkicon = new DeskIcon(this,"");
    dkicon->setIcon(pix);
    dkicon->move(x,y);
    dkicon->show();
    dkicon->setIconText(title);
}
void QDocker::addApp(QString &path, QString &title)
{
    QPixmap &pix = QAppUtils::ref().getAppIcon(path);
    addApp(pix,title,path);
}
