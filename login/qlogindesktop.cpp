#include "qlogindesktop.h"
#include "maindialog.h"
#include <QHBoxLayout>
#include <QWebSettings>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

QLoginDesktop::QLoginDesktop(QWidget *parent) : QWidget(parent)
{
    initUI();
    resize(500,500);
}

void QLoginDesktop::initUI()
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    m_web = new QWebView(this);
    m_web->load(QUrl("html/login.html"));
    m_web->setContextMenuPolicy(Qt::NoContextMenu);
    QWebSettings    *webSetting = m_web->page()->settings();
    webSetting->setAttribute(QWebSettings::JavascriptEnabled,true);
    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addObject()));
    lay->addWidget(m_web);
}

void QLoginDesktop::addObject()
{
    m_web->page()->mainFrame()->addToJavaScriptWindowObject("Login",this);
}

void QLoginDesktop::showMain()
{
    static MainDialog &main = MainDialog::ref();
    main.getStackedWidget()->setCurrentIndex(0);
}
void QLoginDesktop::exitApp()
{
    qApp->exit(0);
}
void QLoginDesktop::msgBox(QString title, QString txt)
{
    QMessageBox::information(this,title,txt,0);
}
void QLoginDesktop::caLogin()
{


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
void QLoginDesktop::downloadSvrList()
{

}
void QLoginDesktop::onSvrDownloadFinish(const char *, const char *)
{

}
