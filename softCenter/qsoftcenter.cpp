#include "qsoftcenter.h"
#include "http/qhttpdownload.h"
#include "jsCore/qjscore.h"
#include "utils/defines.h"
#include "utils/qapputils.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QWebSettings>
#include <QWebFrame>
#include <QCloseEvent>

QSoftCenter* QSoftCenter::m_inst = NULL;

QSoftCenter::QSoftCenter(QWidget *parent) : QDialog(parent)
{
    initUI();
    m_inst = this;
}

void QSoftCenter::initUI()
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    int         wid, hei;
    setWindowTitle(LOCAL("软件中心"));
    lay->setContentsMargins(0,0,0,0);

    m_web = new QHFWebView(this);
    m_web->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    m_web->load(QUrl("html/softCenter.html"));

//    QWebSettings *settings = m_web->page()->settings();
//    settings->setAttribute(QWebSettings::JavascriptEnabled,true);
//    settings->setAttribute(QWebSettings::LocalStorageEnabled,true);
//    settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);

//    connect(m_web->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),
//            this,SLOT(registerObject()));

    connect(m_web,SIGNAL(linkClicked(QUrl)),this,SLOT(linkCliced(QUrl)));
    lay->addWidget(m_web);
    QAppUtils::ref().getScreenSize(wid,hei);
    resize(wid*0.9,600);
    //下载apps.json
    m_web->download_file("http://localhost:8080/Hello/yang?file=apps/apps.json","html/files/apps.json");

}

void QSoftCenter::linkCliced(const QUrl &url)
{
    qDebug()<<url.toString();
    //accept();
}
void QSoftCenter::registerObject()
{
    //QJSCore *core = new QJSCore(this);
    //m_web->page()->mainFrame()->addToJavaScriptWindowObject("Qt",core);
}
void QSoftCenter::closeEvent(QCloseEvent *evt)
{
    qDebug()<<"Close";
    setVisible(false);
    evt->ignore();
}
