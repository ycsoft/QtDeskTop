#include "qjscore.h"
#include "softCenter/qsoftcenter.h"
#include "maindialog.h"
#include "utils/defines.h"

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
