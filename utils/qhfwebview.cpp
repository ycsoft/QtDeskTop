#include "qhfwebview.h"
#include "jsCore/qjscore.h"

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

QHFWebView::QHFWebView(QWidget *parent) : QWebView(parent)
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
    qDebug()<<request.url().toString();
    QString defaultFileName =
       QFileInfo(request.url().toString()).fileName();

    qDebug()<<"Download File:"<<defaultFileName;
     QString fileName =
       QFileDialog::getSaveFileName(this,
                                    tr("Save File"),
                                    defaultFileName);
     if (fileName.isEmpty())
       return;

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
     QFile file(fileName);
     if (file.open(QFile::ReadWrite))
       file.write(reply->readAll());
}
