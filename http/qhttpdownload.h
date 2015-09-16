#ifndef QHTTPDOWNLOAD_H
#define QHTTPDOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class QHttpDownLoad : public QObject
{
    Q_OBJECT
public:
    explicit QHttpDownLoad(QObject *parent = 0);
    void downloadFile(QString url);
public slots:
    void finished();
    void readyRead();
    void error(QNetworkReply::NetworkError);
private:
    QNetworkAccessManager   *m_nam;
    QString                 m_fname;
    QFile                   *m_file;
    QNetworkReply           *m_reply;
    bool                    m_error;
};

#endif // QHTTPDOWNLOAD_H
