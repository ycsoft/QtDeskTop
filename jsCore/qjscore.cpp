#include "qjscore.h"

#include <QFile>
#include <QMessageBox>
#include <QDebug>

#include <QProcess>

QJSCore::QJSCore(QObject *parent) : QObject(parent)
{

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

void QJSCore::open(const QString &path)
{

    QFile file(path);
    if( file.exists())
    {
        qDebug()<<"Open:"<<path;
        QProcess *proc = new QProcess(this);
        proc->start(path);
        proc->waitForStarted(5000);
//        ShellExecuteA(0,"open",path.toUtf8().data(),NULL,NULL,SW_SHOW);
    }else
    {
        qDebug()<<"No File:"<<path;
    }
}
