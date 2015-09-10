#include "qutil.h"
#include "caoper.h"
#include "session.h"

#include <QApplication>
#include <QStringList>
#include <QFile>
#include <QtXml>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QClipboard>


QUtil::QUtil(QObject *parent) :
    QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

QUtil * QUtil::m_instance = NULL;

void QUtil::SplitJIDCode(QString randstr, QString &qjid, QString &qcode)
{
    QStringList list = randstr.split(QRegExp(":"));
    if (list.count() > 1)
    {
        qjid = list.at(0);
        qcode = list.at(1);
    }else
        return;
}
void QUtil::readFileServerPort(const QString fconf, QString &ip, int &port)
{
    QFile file(fconf);
    if (!file.exists())
        return;
    if (!file.open(QIODevice::ReadOnly))
    {
        file.close();
        return;
    }
    while (!file.atEnd())
    {
        QString sline = file.readLine(128);
        if (sline[0] == QChar('#'))
            continue;
        QStringList ls = sline.split("=",QString::SkipEmptyParts);
        if (ls.count() <= 0)
            continue;

        if (ls[0].indexOf("IP") >= 0)
        {

            ip = ls[1];
            ip = ip.trimmed();
        }else if(ls[0].indexOf("Port") >= 0)
        {
            port = ls[1].toInt();
        }

    }
    file.close();
}
QUtil * QUtil::Instance()
{
    if ( NULL == m_instance )
        m_instance = new QUtil(0);
    return m_instance;
}
yswift_apps* QUtil::getAppsFromXml(QString xml)
{
    QDomDocument    dom;
    QDomElement     elem;
    QFile           file;
    yswift_apps     *apps = new yswift_apps;
    file.setFileName(xml);
    if ( ! file.open(QIODevice::ReadOnly) )
        return NULL;
    QString str_xml = QString::fromLocal8Bit(file.readAll());
    if ( !dom.setContent(str_xml))
    {
        file.close();
        return NULL;
    }
    file.close();
    elem = dom.documentElement();
    elem = elem.firstChildElement("app");
    while (!elem.isNull())
    {
        yswift_app  app;
        QString     version = elem.attribute("version","");
        QString     url = elem.attribute("url","");
        QString     name = elem.attribute("name","");
        QDomElement desc = elem.firstChildElement("desc");
        app.version = version;
        app.url = url;
        app.name = name;
        if (!desc.isNull())
        {
            app.desc = desc.lastChild().nodeValue();
        }

        QDomElement elem_size = elem.firstChildElement("size");
        if ( !elem_size.isNull())
        {
           QString str_size = elem_size.lastChild().nodeValue();
           app.size = str_size.toInt();
        }
        QDomElement elem_author = elem.firstChildElement("author");
        if ( !elem_author.isNull() )
        {
            QString str_author = elem_author.lastChild().nodeValue();
            app.author = str_author;
        }
        apps->append(app);
        elem = elem.nextSiblingElement("app");
    }
    return apps;
}
QString QUtil::createDCode()
{
    QClipboard *board = QApplication::clipboard();
    QString     code = CAOper::getCode();
    QString     toboard = Session::Instance()->getJID() + ":" + code;
    board->setText(toboard);

    return code;
}

QString QUtil::getUpdatePage()
{
    QString ret;
    QFile file("config/update.conf");
    if (!file.exists())
    {
        qDebug()<<"no config file named 'update.conf'";
        return "";
    }
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"can not open update.conf";
        file.close();
        return "";
    }
    while( !file.atEnd())
    {
        QString line = file.readLine();
        if( line.indexOf("mainpage") < 0)
            continue;
        int pos = line.indexOf("=");
        QString substr = line.right(line.length() - pos-1);
        ret = substr.trimmed();
        break;
    }
    file.close();
    return ret;
}
QString QUtil::size2string(int size)
{
    char c_size[16] = {0};
    float ksize = size / 1024.0f;
    sprintf(c_size,"%.1f K",ksize);
    ksize = ksize / 1024.0f;
    if (ksize > 1)
        sprintf(c_size,"%.1f M",ksize/1024.0f);
    return QString::fromAscii(c_size);
}

void QUtil::sendFile(QString fn,QString to )
{
    /*
    TransProgress *tp = new TransProgress(0);
    tp->setFileName(fn);
    tp->setSendTo(to);
    tp->exec();
    delete tp;
    */
}

QUtil::~QUtil()
{
    if ( m_instance )
        delete m_instance;
    m_instance = NULL;
}
