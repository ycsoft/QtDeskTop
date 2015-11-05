#include "qjscore.h"
#include "softCenter/qsoftcenter.h"
#include "maindialog.h"
#include "utils/defines.h"
#include "http/qhttpdownload.h"
#include "app/qaccountmgr.h"
#include "login/qutil.h"
#include "login/session.h"

#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <string>
#include <QApplication>
#include <QTextCodec>
#include <Windows.h>
#include <ShellAPI.h>
#include <QTextCodec>
#include <QTextStream>
#include <QSettings>
#include <QClipboard>

using namespace std;


QJSCore::QJSCore(QObject *parent) : QObject(parent),m_pgsql(NULL)
{
    m_acct = new QAccountMgr( & MainDialog::ref());
}
QJSCore::~QJSCore()
{
    if( m_pgsql )
    {
        qDebug()<<"Destroy pgsql";
        delete m_pgsql;
    }
}
void QJSCore::saveData(const QString &fn, const QString &data)
{
    QFile file(fn);
    if ( ! file.open( QIODevice::WriteOnly ))
    {
        return;
    }
    QTextStream output( &file );
    output.setCodec("utf-8");
    output<<data;
    file.close();
}

QString QJSCore::readFromFile(const QString &fn)
{
    QString result;
    QFile file(fn);
    qDebug()<<fn;
    if ( !file.exists() )
    {
        qDebug()<<"No This File";
        return result;
    }
    file.open(QIODevice::ReadOnly);
    result = QString::fromUtf8(file.readAll());
    qDebug()<<result;
    file.close();
    return result;
}

void QJSCore::msgBox(const QString &title,const QString &txt)
{
    qDebug()<<"MsgBox";
    QMessageBox::information(NULL,title,txt,0);
}
void QJSCore::close()
{
    qApp->exit(0);
}
void QJSCore::exec(const QString &path)
{
    QFile file(path);

    if( path == tr("AcctMgr"))
    {
        showAcct();
        return;
    }
    if ( !file.exists() )
    {
        qDebug()<<"No File";
        return;
    }
    ShellExecuteA(0,"open",path.toLocal8Bit().data(),NULL,NULL,SW_SHOW);
}
void QJSCore::open(const QString &path)
{

    QFile file(path);
    if( file.exists())
    {
        qDebug()<<"Open:"<<path;
        QProcess *proc = new QProcess(this);
        proc->start(path);
        proc->waitForStarted(5000);
    }else
    {
        qDebug()<<"No File:"<<path;
    }
}
void QJSCore::open(const QString &path, const QStringList &arglist)
{
    QFile file(path);
    for ( int i = 0 ; i < arglist.count(); ++i)
    {
        qDebug()<<arglist.at(i);
    }

    if( file.exists())
    {
        qDebug()<<"Open:"<<path;
        QProcess *proc = new QProcess(this);
        proc->start(path,arglist);
        proc->waitForStarted(5000);

    }else
    {
        qDebug()<<"No File:"<<path;
    }
}

QString QJSCore::showWindow(QString win)
{
    if ( win == "softcenter" )
    {
        QSoftCenter *soft = QSoftCenter::ref();
        soft->exec();
        return "soft";
    }else if ( win == "switch")
    {
        QStackedWidget *pstack = MainDialog::ref().getStackedWidget();

        int idx = pstack->currentIndex();
        idx = ( idx == Simple_Desk ? Full_Desk : Simple_Desk);
//        pstack->setCurrentIndex(idx);
        return "123";
    }else
        return "";
}

int QJSCore::connectDB(QString host,int port, QString dbname, QString usr, QString pwd)
{
    PGConfigure  conf;
    conf.host = host.toStdString();
    conf.dbname = dbname.toStdString();
    conf.usr = usr.toStdString();
    conf.pwd = pwd.toStdString();
    conf.port = port;
    m_pgsql = new HFPGSql();
    qDebug()<<"Host:"<<host<<" dbname:"<<dbname;
    if ( m_pgsql->connectDB(&conf) )
    {
        qDebug()<<"Connected";
        return 0;
    }else
    {
        qDebug()<<"Connect Error";
        return -1;
    }
}

void QJSCore::executeSQL(QString sql)
{
    m_pgsql->querySQL(sql.toStdString());
}

int QJSCore::getRecordCount()
{
    return m_pgsql->getRecordCount();
}
int QJSCore::getColumnCount()
{
    return m_pgsql->getColumnCount();
}
QString QJSCore::fieldValue(int row, int col)
{
    QString res = QString::fromUtf8( m_pgsql->fieldValue(row,col).c_str() );
    return res;
}

void QJSCore::download(QString url)
{
//    QHttpDownLoad *down = new QHttpDownLoad(this);
//    down->downloadFile(url);
    QHFWebView *hf = new QHFWebView( & MainDialog::ref());
    hf->download(QNetworkRequest(QUrl(url)));
}

void QJSCore::download(QString url, QString savepath)
{
    QHFWebView *hf = new QHFWebView( & MainDialog::ref());
    hf->download_file(url,savepath);
}

QString QJSCore::nameFromURL(QString url)
{
    QFileInfo info(url);
    return info.fileName();
}

void QJSCore::executeSQL(QString sql, QString etti)
{
    QString js = "$(this).popTips('#todo',translate2txt(JSON.parse(res)),sql,txt);";
}

void QJSCore::showTips()
{
    m_tips = new QTipsWidget();
    m_tips->exec();
}
void QJSCore::tips_agree()
{
    QString js =  QString::fromLocal8Bit(
                    "todoNum -= 1;"
                    "done += 1;"
                    "curItem.css('display','none');"
                    "$('#headtodo').setNumber(todoNum);"
                    "$('#headdone').setNumber(done);"
                    "var flow = Qt.readValue('param');"
                    "$('#done').addItem(flow,'删除',2);"
                    "Qt.executeSQL(sql);"
                    "$('#todo').css('height','70%');"
                    "$('.tips').css('display','none');"
                    "$('#btmdock').css('bottom','50px');"

                );

    MainDialog::ref().getMainFrame()->runJS(js);
    m_tips->accept();
    m_tips->deleteLater();
}
void QJSCore::tips_reject()
{
    m_tips->reject();
    m_tips->deleteLater();
}

void QJSCore::saveValue(QString key, QString value)
{
    QSettings   set;
    qDebug()<<"set key:"<<key<<" value:"<<value;
    set.setValue(key,value);
}
QString QJSCore::readValue(QString key)
{
    QSettings set;
    return set.value(key).toString();
}

void QJSCore::showAcct()
{

    m_acct->show();
}
void QJSCore::hideAcct()
{
    m_acct->hide();
}
QString QJSCore::getDCode()
{
    QString code = QUtil::Instance()->createDCode();
    qDebug()<<"Dynamic Code is:"<<code;

    return code;
}




