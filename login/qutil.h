#ifndef QUTIL_H
#define QUTIL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtNetwork>

struct yswift_app
{
    int         size;
    QString     version;
    QString     name;
    QString     desc;
    QString     url;
    QString     author;
};
typedef QList<yswift_app> yswift_apps;

class QUtil : public QObject
{
    Q_OBJECT
public:
    explicit QUtil(QObject *parent = 0);
    ~QUtil();

    static void SplitJIDCode(QString randstr,QString &qjid, QString &qcode);
    static void readFileServerPort(const QString fconf, QString &ip, int &port);

    static  QUtil*  Instance();
    static  QString getUpdatePage();
    static  QString size2string(int size);
    static  QString    createDCode();

    static  void    sendFile(QString fn,QString ro);
    yswift_apps*    getAppsFromXml(QString xml);
signals:

public slots:

private:
    static QUtil *m_instance;

    QNetworkAccessManager       *m_manager;
    QNetworkReply               *m_reply;
};

#endif // QUTIL_H
