#include "qlogindesktop.h"
#include "maindialog.h"
#include "data/qluaconf.h"
#include "caoper.h"
#include "utils/defines.h"
#include "tcpserver.h"
#include "taskbar.h"
#include "jsCore/qjscore.h"
#include "utils/qapparg.h"

#include <QHBoxLayout>
#include <QWebSettings>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QNetworkCookieJar>

QLoginDesktop::QLoginDesktop(QWidget *parent) : QWidget(parent)
{
    initUI();
    resize(500,500);
    m_client = new QFileTrans(this);
    connect(m_client,SIGNAL(connected()),this,SLOT(connected()));
    connect(m_client,SIGNAL(disconnected()),this,SLOT(connectedError()));
}
QLoginDesktop::~QLoginDesktop()
{
    qDebug()<<"QLoginDesktop destroy";
}

void QLoginDesktop::initUI()
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    m_web = new QHFWebView(this);
    m_web->load(QUrl("html/login.html"));
    m_web->page()->networkAccessManager()->setCookieJar(new QNetworkCookieJar(this));
    QWebSettings    *webSetting = m_web->page()->settings();
    webSetting->setAttribute(QWebSettings::JavascriptEnabled,true);
    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addObject()));
    lay->addWidget(m_web);
}

void QLoginDesktop::addObject()
{
    QLuaConf *conf = new QLuaConf(this);
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("Conf",conf);
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("Login",this);
}

void QLoginDesktop::showMain()
{
    static MainDialog &main = MainDialog::ref();
    main.getTaskBar()->setVisible(true);
    main.getStackedWidget()->setCurrentIndex( Simple_Desk );
}
void QLoginDesktop::exitApp()
{
    qApp->exit(0);
}
void QLoginDesktop::msgBox(QString title, QString txt)
{
    QMessageBox::information(this,title,txt,0);
}
void QLoginDesktop::caLogin(QString host,QString ip)
{
    QString         qorigin = CAOper::getOrigin();
    QString         usr;
    CAOper          oper;
    QString         sign = oper.buildAuthRequest(tr(""),qorigin);
    QSettings       set;
    usr = qorigin;
    m_client->login(usr,sign,host,ip,QFileTrans::CA);
}
void QLoginDesktop::upLogin(QString usr, QString pwd, QString host, QString ip)
{
    m_client->login(usr,pwd,host,ip);

    //usr = QCryptographicHash::hash(usr.toLocal8Bit(),QCryptographicHash::Md5).toHex();

}

QStringList  QLoginDesktop::readConfig()
{
    QSettings   set;
    downloadSvrList();
    QString usr = set.value("usr","").toString();
    QString svr = set.value("svr","").toString();
    QString ip  = set.value("ip","127.0.0.1").toString();
    QString pwd = set.value("pwd","").toString();
    if (ip.isEmpty())
    {
        ip = "127.0.0.1";
        set.setValue("ip",ip);
    }
    return QStringList()<<usr<<pwd<<svr<<ip;
}

void QLoginDesktop::connected()
{
    showMain();
    //XMPP连接建立以后启动socket本地服务
    static boost::asio::io_service g_io;
    TCPServer *m_svrsock = new TCPServer(g_io,5033,this);
    //准备启动即时通信
    QJSCore *jscore = QJSCore::ref();
    QStringList arglist = QAppArg::ref().argList();
    jscore->open("IM_QXmpp.exe",arglist);
}

void QLoginDesktop::connectedError()
{
    msgBox(LOCAL("错误"),LOCAL("未登陆"));
}

void QLoginDesktop::csleep(int millisec)
{
    Sleep(millisec);
}

void QLoginDesktop::downloadSvrList()
{

}
void QLoginDesktop::onSvrDownloadFinish(const char *, const char *)
{

}
