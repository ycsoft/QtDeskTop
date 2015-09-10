#include "qfloaticon.h"
#include "caoper.h"
#include "qutil.h"
#include "session.h"
#include "maindialog.h"
#include "qxmpppacketconsle.h"
#include "ftapi.h"
#include "qfilelist.h"
#include "datatypes.h"
#include "mysock.h"
#include "qsysnotehistory.h"
#include "qviewnote.h"
#include "qdownloadprogress.h"

#include <QPainter>
#include <QMenu>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QClipboard>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>





QFloatIcon::QFloatIcon(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
}

void QFloatIcon::onExit()
{
    QApplication::exit(0);
}

void QFloatIcon::setupUI()
{
    setWindowFlags(Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint
                   | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setFocusPolicy(Qt::NoFocus);
    resize(100,100);

}
void QFloatIcon::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton){
        m_currentPos = event->globalPos()- frameGeometry().topLeft();
        event->accept();
    }
}
void QFloatIcon::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton){
        move(event->globalPos() - m_currentPos );
        event->accept();
    }
}
void QFloatIcon::paintEvent(QPaintEvent *event)
{
    QPainter  painter(this);
    painter.drawPixmap(0,0,m_pixmap);
}
void QFloatIcon::leaveEvent(QEvent *event)

{
    setCursor(Qt::ArrowCursor);
}
void QFloatIcon::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);
}
void QFloatIcon::onGetDynamicCode()
{
    QString code = QUtil::createDCode();
    qDebug()<<code;
    Session::Instance()->setDCode("app",code);
    QMessageBox::information(this,LOCAL("信息"),LOCAL("认证码已拷贝"));
}
/**
 * @brief QFloatIcon::onUpdate
 *
 * 连接文件更新服务器，进行文件更新
 */
void QFloatIcon::onUpdate()
{
    datatype::getFileList   gt;
    QFileList   *flist = new QFileList(0);
    QString qjid = Session::Instance()->getHostName();
    FTAPI::Instance()->getSock()->getFileList().clear();
    bool bcheck;
    bcheck = connect(FTAPI::Instance()->getSock(),SIGNAL(addShareFile(const char*)),flist,SLOT(addShareFile(const char*)));
    char    jid[JID_LEN] = {0};
    memcpy_s(jid,JID_LEN,qjid.toLocal8Bit().data(),qjid.toLocal8Bit().length());
    memcpy_s(gt.fromjid,JID_LEN,jid,JID_LEN);
    FTAPI::Instance()->senddata(&gt,sizeof(gt));
    flist->show();
    flist->activateWindow();
}

void QFloatIcon::mouseDoubleClickEvent(QMouseEvent *event)
{
    QString code = QUtil::createDCode();
    qDebug()<<code;
    Session::Instance()->setDCode("app",code);
    //MainDialog::Instance()->showXmppConsle();
    QMessageBox::information(this,LOCAL("信息"),LOCAL("认证码已拷贝"));
}

void QFloatIcon::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    update();
}
void QFloatIcon::onViewSysNote()
{
    MainDialog::Instance()->resetCount();
    MainDialog::Instance()->getViewNoteDlg()->hide();
    QSysNoteHistory *note = new QSysNoteHistory(0);
    note->show();
}

void QFloatIcon::setContextMenu(QMenu *menu)
{
    _ctxMenu = menu;
}
/**
 * @brief QFloatIcon::contextMenuEvent
 * @param event
 *
 * 构造右键弹出菜单
 */
void QFloatIcon::contextMenuEvent(QContextMenuEvent *event)
{
    QCursor cur = this->cursor();
    QMenu *menu = new QMenu(this);
    QAction *item_code = new QAction(this);
    item_code->setText(LOCAL("获取认证码"));
    item_code->setIcon(QIcon(":/UI/dcode.png"));
    menu->addAction(item_code);

    QAction *item_viewnote = new QAction(this);
    item_viewnote->setText(LOCAL("查看通知"));
    item_viewnote->setIcon(QIcon(":/UI/dcode.png"));
    menu->addAction(item_viewnote);

    /*
    QAction *item_update = new QAction(this);
    item_update->setText(LOCAL("软件升级"));
    item_update->setIcon(QIcon(":/UI/update.png"));
    menu->addAction(item_update);
    */

    QAction *item_exit = new QAction(this);
    item_exit->setIcon(QIcon(":/UI/exit.png"));
    item_exit->setText(LOCAL("退出"));
    menu->addAction(item_exit);
    bool    bcheck;

    bcheck = connect(item_code,SIGNAL(triggered()),this,SLOT(onGetDynamicCode()));
    Q_ASSERT(bcheck);

    //bcheck = connect(item_update,SIGNAL(triggered()),this,SLOT(onSoftUpdate()));
    //Q_ASSERT(bcheck);

    bcheck = connect(item_exit,SIGNAL(triggered()),this,SLOT(onExit()));
    Q_ASSERT(bcheck);

    bcheck = connect(item_viewnote,SIGNAL(triggered()),this,SLOT(onViewSysNote()));
    Q_ASSERT(bcheck);

    menu->exec(cur.pos());
}
void QFloatIcon::moveToRightTop()
{
    int wid = QApplication::desktop()->width();
    int hei = QApplication::desktop()->height();
    int cw = this->width();
    int ch = this->height();
    this->move(wid-2*cw,40);
}
/**
 * @brief QFloatIcon::onSoftUpdate
 * 软件升级，先下载配置文件，检查版本号，然后根据
 * 版本号决定是否更新
 */
void QFloatIcon::onSoftUpdate()
{
    bool bcheck = connect(FTAPI::Instance()->getSock(),
                          SIGNAL(finished(const char*,const char*)),this,
                          SLOT(finished(const char*,const char*)));
    if (!FTAPI::Instance()->getSock()->isconnected())
    {
        FTAPI::Instance()->close();
        QSettings   set;
        QString     ip = set.value("ip",Default_IP).toString();
        FTAPI::Instance()->login(QHostInfo::localHostName().toLocal8Bit().data(),ip.toLocal8Bit().data(),7000);
    }else
    {
        //本身已经连接
        FTAPI::Instance()->close();
        QSettings set;
        QString     ip = set.value("ip",Default_IP).toString();
        FTAPI::Instance()->login(QHostInfo::localHostName().toLocal8Bit().data(),ip.toLocal8Bit().data(),7000);
    }
    if (!FTAPI::Instance()->getSock()->isconnected())
    {
        QMessageBox::warning(this,LOCAL("警告"),
                             LOCAL("无法连接更新服务器，可能IP设置有误或服务器出现故障"),0,1);
        return;
    }
    FTAPI::Instance()->downloadFile("SafeThrough.ini");
    Q_ASSERT(bcheck);
}
/**
 * @brief QFloatIcon::finished
 * @param from
 * @param filename
 * 下载完毕，解析版本号
 */
void QFloatIcon::finished(const char *from, const char *filename)
{
    QSettings   set("SafeThrough.ini",QSettings::IniFormat);
    qreal       ver = set.value("version","0.0").toFloat();
    bool bcheck = disconnect(FTAPI::Instance()->getSock(),
                             SIGNAL(finished(const char*,const char*)),this,
                             SLOT(finished(const char*,const char*)));
    //Q_ASSERT(bcheck);
    if (ver > CURRENT_VERSION)
    {
        QDownloadProgress   *progress = new QDownloadProgress(0);
        //
        //此处不再绑定下载完毕信号，通过下载进度可以自行判断下载是否完成
        //
        bcheck = connect(FTAPI::Instance()->getSock(),SIGNAL(signalprogress(uint,uint)),progress,SLOT(progress(uint,uint)));
        Q_ASSERT(bcheck);
        progress->show();
        qDebug()<<"Down load Main App............";
        FTAPI::Instance()->downloadFile(Installer_Name);
    }else
    {
        QMessageBox::information(this,"Tip",LOCAL("当前已是最新版本"),0);
    }

}
