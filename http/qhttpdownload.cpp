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
    m_file = new QFile(fn);
    qDebug()<<"File Name: "<<fn;
    if ( m_file->exists() )
    {
        int res = 0;
        //QString title = LOCAL("提示"), text = LOCAL("文件已存在，是否重复下载?");
        //res = QMessageBox::information(NULL,title,text,QMessageBox::Yes,QMessageBox::No);
        res = QMessageBox::Yes;
        if ( res != QMessageBox::Yes)
        {
            delete m_file;
            m_file = NULL;
            qDebug()<<"Do not overwrite";
        }else
        {
            qDebug()<<"Overwrite";
            m_file->open(QIODevice::WriteOnly);
            QNetworkRequest &request = QNetworkRequest(QUrl(url));
            m_error = false;
            m_reply = m_nam->get(request);
            connect(m_reply,SIGNAL(readyRead()),this,SLOT(readyRead()));
            connect(m_reply,SIGNAL(finished()),this,SLOT(finished()));
            connect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(error(QNetworkReply::NetworkError)));

        }
    }else
    {
        qDebug()<<"Download";
        m_file->open(QIODevice::WriteOnly);
        QNetworkRequest &request = QNetworkRequest(QUrl(url));
        m_error = false;
        m_reply = m_nam->get(request);
        connect(m_reply,SIGNAL(readyRead()),this,SLOT(readyRead()));
        connect(m_reply,SIGNAL(finished()),this,SLOT(finished()));
        connect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(error(QNetworkReply::NetworkError)));

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

    if ( !m_error )
    {
        QMessageBox::information(NULL,LOCAL("已完成"),LOCAL("文件下载完毕"),0);
    }else
    {
        QMessageBox::information(NULL,LOCAL("错误"),LOCAL("文件下载出错"),0);
    }
    m_file->close();
    delete m_file;

}
void QHttpDownLoad::error(QNetworkReply::NetworkError err)
{
    qDebug()<<"Error:"<<err;

    m_reply->close();
    m_reply->deleteLater();

    if ( err != QNetworkReply::NoError)
    {
        m_error = true;
    }
}
