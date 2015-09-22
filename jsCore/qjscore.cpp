#include "qjscore.h"
#include "softCenter/qsoftcenter.h"
#include "maindialog.h"
#include "utils/defines.h"

#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <string>
#include <QApplication>

using namespace std;


QJSCore::QJSCore(QObject *parent) : QObject(parent),m_pgsql(NULL)
{

}
QJSCore::~QJSCore()
{
    if( m_pgsql )
    {
        delete m_pgsql;
    }
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

void QJSCore::showWindow(QString win)
{
    if ( win == "softcenter" )
    {
        static QSoftCenter soft;
        soft.show();
    }else if ( win == "switch")
    {
        QStackedWidget *pstack = MainDialog::ref().getStackedWidget();

        int idx = pstack->currentIndex();
        idx = ( idx == Simple_Desk ? Full_Desk : Simple_Desk);
        pstack->setCurrentIndex(idx);
    }
}

int QJSCore::connectDB(QString host, QString dbname, QString usr, QString pwd)
{
    PGConfigure  conf;
    conf.host = host.toStdString();
    conf.dbname = dbname.toStdString();
    conf.usr = usr.toStdString();
    conf.pwd = usr.toStdString();
    m_pgsql = new HFPGSql();
    if ( m_pgsql->connectDB(&conf) )
    {
        return 0;
    }else
    {
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
