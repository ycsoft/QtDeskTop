#include "qsoftcenter.h"
#include "http/qhttpdownload.h"

#include <QHBoxLayout>
#include <QDebug>

QSoftCenter::QSoftCenter(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void QSoftCenter::initUI()
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    m_web = new QHFWebView(this);
    m_web->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    m_web->load(QUrl("html/softCenter.html"));
    connect(m_web,SIGNAL(linkClicked(QUrl)),this,SLOT(linkCliced(QUrl)));
    lay->addWidget(m_web);
    resize(600,400);
}

void QSoftCenter::linkCliced(const QUrl &url)
{
    qDebug()<<url.toString();
    QHttpDownLoad *download = new QHttpDownLoad(this);
    download->downloadFile(url.toString());
}
