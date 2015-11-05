#include "qhfwebview.h"
#include "jsCore/qjscore.h"

#include "softCenter/qsoftcenter.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QPalette>
#include <QMouseEvent>
#include <QWebSettings>
#include <QWebFrame>
#include <QNetworkReply>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QDir>

#include <Windows.h>
#include <ShellAPI.h>

QHFWebView::QHFWebView(QWidget *parent) : QWebView(parent),m_filepath("html/files"),m_bfinished(false)
{

}


//void QHFWebView::paintEvent(QPaintEvent *evt)
//{
//    QPainter p;
//    QStyleOption op;

//    //QWebView::paintEvent(evt);

//    op.init(this);
//    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);
//}

void QHFWebView::mouseDoubleClickEvent(QMouseEvent *evt)
{
    evt->ignore();
}

void QHFWebView::setTransparent(bool )
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base,Qt::transparent);

    this->page()->setPalette(palette);
    setAttribute(Qt::WA_OpaquePaintEvent,false);
}

void QHFWebView::registerObject()
{
    QJSCore *core = QJSCore::ref();
    page()->mainFrame()->addToJavaScriptWindowObject("Qt",core);
}

void QHFWebView::load(const QUrl &url)
{
    QWebView::load(url);
    QWebSettings *sets = this->page()->settings();
    sets->setAttribute(QWebSettings::JavascriptEnabled,true);
    sets->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);
    sets->setAttribute(QWebSettings::LocalStorageEnabled,true);
    connect(page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(registerObject()));
}
void QHFWebView::download(const QNetworkRequest &request)
{
    qDebug()<<"URL:"<<m_url;
    m_bfinished = false;
    qDebug()<<request.url().toString();
    QString defaultFileName =
       QFileInfo(request.url().toString()).fileName();

    qDebug()<<"Download File:"<<defaultFileName;
     QString fileName = m_filepath;
//       QFileDialog::getSaveFileName(this,
//                                    tr("Save File"),
//                                    defaultFileName);
//     if (fileName.isEmpty())
//       return;

     // Construct a new request that stores the
     // file name that should be used when the
     // download is complete
     QNetworkRequest newRequest = request;
     newRequest.setAttribute(QNetworkRequest::User,
                             fileName);

     // Ask the network manager to download
     // the file and connect to the progress
     // and finished signals.
     QNetworkAccessManager *networkManager =
      page()->networkAccessManager();
     QNetworkReply *reply =
       networkManager->get(newRequest);

     connect(reply,SIGNAL(finished()),this,SLOT(downloadFinish()));
}
void QHFWebView::downloadFinish()
{
     QNetworkReply *reply = ((QNetworkReply*)sender());
     QNetworkRequest request = reply->request();
     QVariant v =
       request.attribute(QNetworkRequest::User);
     QString fileName = v.toString();
     QString pureName;
     QFile file(fileName);
     QFileInfo info(fileName);

     pureName = info.fileName();
     pureName = pureName.left(pureName.lastIndexOf(".exe"));
     qDebug()<<"Pure Name:"<<pureName;

     if (file.open(QFile::ReadWrite))
     {
        file.write(reply->readAll());
        file.close();
     }

     m_bfinished = true;
     QString cur = QDir().currentPath() +"/" + m_filepath;
     if( cur.endsWith(".exe") )
     {
        ShellExecuteA(0,"open",cur.toLocal8Bit().data(),NULL,NULL,SW_SHOW);
        QString js = QString("installOk('%1','%2')").arg(pureName).arg(m_url);
        QSoftCenter::ref()->runJS(js);
     }

}

void QHFWebView::download_file(QString path, QString savepath)
{
    m_filepath = savepath;
    m_url = path;
    download(QNetworkRequest(QUrl(path)));
}
