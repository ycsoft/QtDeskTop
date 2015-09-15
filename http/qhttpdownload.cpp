#include "qhttpdownload.h"
#include "utils/defines.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

QHttpDownLoad::QHttpDownLoad(QObject *parent) : QObject(parent)
  ,m_nam(new QNetworkAccessManager(this)),m_file(NULL)
{

}

void QHttpDownLoad::downloadFile(QString url)
{
    QFileInfo   info(url);
    QString     fn =  info.fileName();
    QNetworkRequest &request = QNetworkRequest(QUrl(url));

    m_reply = m_nam->get(request);
    connect(m_reply,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(m_reply,SIGNAL(finished()),this,SLOT(finished()));
    connect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(error(QNetworkReply::NetworkError)));
    m_file = new QFile(fn);
    qDebug()<<"File Name: "<<fn;
    if ( m_file->exists() )
    {
        int res = 0;
        QString title, text;
        res = QMessageBox::information(NULL,title,text,QMessageBox::Yes,QMessageBox::No);
        if ( res != QMessageBox::Yes)
        {
            delete m_file;
            m_file = NULL;
        }
    }else
    {
        m_file->open(QIODevice::WriteOnly);
    }
}

void QHttpDownLoad::readyRead()
{
    if ( NULL != m_file )
    {
        m_file->write( m_reply->readAll());
    }
}
void QHttpDownLoad::finished()
{
    qDebug()<<"Download Finished";
    if ( NULL != m_file )
    {
        m_file->close();
    }
    delete m_file;
    m_reply->deleteLater();
}
void QHttpDownLoad::error(QNetworkReply::NetworkError err)
{
    qDebug()<<"Error:"<<err;
}
