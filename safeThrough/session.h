#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QHash>

class Session : public QObject
{
    Q_OBJECT
public:
    ~Session();


public:
    static Session* Instance();

    void setFileIp(QString ip)
    {
        fileIp_ = ip;
    }
    QString getFileIp()
    {
        return fileIp_;
    }
    void setFilePort(int port)
    {
        filePort_ = port;
    }
    int getFilePort()
    {
        return filePort_;
    }

    void setHostName(QString name)
    {
        hostname_ = name;
    }
    QString getHostName()
    {
        return hostname_;
    }

    void setHostIp(QString ip)
    {
        hostip_ = ip;
    }
    QString getHostIp()
    {
        return hostip_;
    }

    void setHostPort( int port )
    {
        hostport_ = port;
    }
    int getHostPort()
    {
        return hostport_;
    }

    void setJID(QString jid)
    {
        jid_  = jid;
    }
    QString getJID()
    {
        return jid_;
    }
    void    setDCode(QString app,QString code)
    {
        dcodes_[app] = code;
    }
    QString getCode(QString app)
    {
        return dcodes_[app];
    }
    void SetPassWord(QString pwd)
    {
        m_pwd = pwd;
    }
    QString GetPassWord()
    {
        return m_pwd;
    }

    void setAppName(QString app) { appName_ = app;}
    QString getAppName() const { return appName_;}


    bool  GetConfirmed() { return m_bconfirmed;}
    void  SetConfirmed(bool b) { m_bconfirmed = b;}
signals:

public slots:

private:
    explicit Session(QObject *parent = 0);

    static Session          * m_instance;
    QString                 hostname_;
    QString                 hostip_;
    int                     hostport_;
    QString                 jid_;
    QString                 m_pwd;
    QString                 fileIp_;

    QString                 appName_;

    int                     filePort_;
    QHash<QString,QString>  dcodes_;
    bool                    m_bconfirmed;
};

#endif // SESSION_H
