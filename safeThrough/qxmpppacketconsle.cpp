#include "qxmpppacketconsle.h"
#include "ui_qxmpppacketconsle.h"
#include "session.h"
#include "CommandParse.hpp"
#include "qfloaticon.h"
#include "maindialog.h"
#include "qfiletrans.h"

#include <QXmppUtils.h>
#include <QFile>
#include <QMessageBox>
#ifndef LOCAL(X)
#define LOCAL(X) QString::fromLocal8Bit(X)
#endif



QXmppPacketConsle::QXmppPacketConsle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QXmppPacketConsle)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/UI/app.png"));
}

QXmppPacketConsle::~QXmppPacketConsle()
{
    delete ui;
}
void QXmppPacketConsle::closeEvent(QCloseEvent *e)
{
    hide();
    saveHistory();
    e->ignore();
}

void QXmppPacketConsle::logMessage(QXmppLogger::MessageType type,QString msg)
{
    static int logcount = 0;
    int     ret = 0;
    QString omsg = msg;
    ++logcount;
    if (logcount > MAX_MESSAGE_SHOW)
    {
        logcount = 0;
        saveHistory();
        ui->textEdit->clear();
    }
    if ( type != QXmppLogger::ReceivedMessage && type != QXmppLogger::SentMessage)
        return;
    if (type == QXmppLogger::ReceivedMessage)
    {
        msg = "In:\n" + msg;
        ui->textEdit->setTextColor(Qt::red);
        /**
         *处理特殊格式的报文
         */
        QString result,result2;
        bool b = CommandParse::parseRandCodeIq(omsg,result,ret,result2);
        qDebug()<<result;
        qDebug()<<"Parse Return: "<<ret;
        if ( b )
        {
           //if (QMessageBox::Yes ==  QMessageBox::information(this,LOCAL("提示"),LOCAL("未知用户通过验证，是否同意其启动"),QMessageBox::Yes | QMessageBox::No))
           {
               MainDialog::Instance()->getClient()->sendData(result.toUtf8());
           }
        }else if ( ret == 0)
        {
            QFloatIcon *flt = MainDialog::Instance()->getFloatDlg();
            if (QMessageBox::Yes ==  QMessageBox::information(flt,
                                                              LOCAL("提示"),
                                                              LOCAL("是否同意其启动"),
                                                              QMessageBox::Yes | QMessageBox::No))
            {
                MainDialog::Instance()->getClient()->sendData(result2.toUtf8());
            }else
                MainDialog::Instance()->getClient()->sendData(result.toUtf8());
        }
    }
    else if ( type == QXmppLogger::SentMessage)
    {
        msg = "Out:\n" + msg;
        ui->textEdit->setTextColor(Qt::black);
    }
    ui->textEdit->append(msg);
    ui->textEdit->append("\r\n");


}
void QXmppPacketConsle::returnPressed()
{
    QString data = ui->lineEdit->text();
    MainDialog::Instance()->getClient()->sendData(data.toUtf8());
}

void QXmppPacketConsle::saveHistory()
{
    QString str = ui->textEdit->toPlainText();
    QString barejid = QXmppUtils::jidToBareJid(Session::Instance()->getJID());
    QFile f( barejid + ".history");
    if ( !f.open(QIODevice::Append))
    {
        f.close();
        return;
    }
    f.write(str.toLocal8Bit());
    f.flush();
    f.close();
}
