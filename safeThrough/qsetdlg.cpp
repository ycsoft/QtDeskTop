#include "qsetdlg.h"
#include "ui_qsetdlg.h"
#include "ftapi.h"
#include "mysock.h"
#include "maindialog.h"
#include "qfloaticon.h"

#include <QSettings>
#include <QFile>
#include <QHostInfo>
#include <QMessageBox>

QSetDlg::QSetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSetDlg)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("高级设置"));
    bool bcheck;
    bcheck = connect(ui->pushButtonApply,SIGNAL(clicked()),this,SLOT(onApplyClick()));
    Q_ASSERT(bcheck);

    //bcheck = connect(ui->pushButtonExit,SIGNAL(clicked()),
    //                 MainDialog::Instance()->getFloatDlg(),SLOT(onSoftUpdate()));
    //Q_ASSERT(bcheck);

    bcheck = connect(ui->pushButtonExit,SIGNAL(clicked()),
                     this,SLOT(onUpdateClick()));
    Q_ASSERT(bcheck);

    bcheck = connect(ui->lineEditIP,SIGNAL(textEdited(QString)),this,SLOT(textEdited(QString)));
    Q_ASSERT(bcheck);

    QSettings set;
    QString ip;
    ip = set.value("ip","10.77.1.114").toString();
    //port = set.value("file_port","7000").toString();
    ui->lineEditIP->setText(ip);
    //ui->lineEditPort->setText(port);
}

void QSetDlg::onUpdateClick()
{
    ui->pushButtonExit->setEnabled(false);
    ui->pushButtonApply->setEnabled(false);
    QSettings   set;
    QString     ip;
    ip = ui->lineEditIP->text();
    set.setValue("ip",ip);
    ui->lineEditIP->setEnabled(false);
    ui->pushButtonApply->setEnabled(false);
    MainDialog::Instance()->getFloatDlg()->onSoftUpdate();

}

QSetDlg::~QSetDlg()
{
    delete ui;
}
/**
 * @brief QSetDlg::onApplyClick
 *
 * 保存用户的设置。该设置主要针对文件服务器
 *
 */
void QSetDlg::onApplyClick()
{
    hide();
    ui->pushButtonApply->setEnabled(false);
    QSettings   set;
    QString     ip;
    ip = ui->lineEditIP->text();
    set.setValue("ip",ip);
    if ( FTAPI::Instance()->getSock()->isconnected())
    {
        FTAPI::Instance()->close();
    }
    FTAPI::Instance()->login(QHostInfo::localHostName().toLocal8Bit().data(),ip.toUtf8().data(),7000);
    if ( !FTAPI::Instance()->getSock()->isconnected())
    {
        QMessageBox::warning(this,LOCAL("警告"),
                             LOCAL("无法连接更新服务器，可能IP设置有误或服务器出现故障"),0,1);
        ui->pushButtonApply->setEnabled(true);
        return;
    }
    MainDialog::Instance()->downloadSvrList();
    close();

}
/**
 * @brief QSetDlg::onUpdate
 *
 *
 */
/*
void QSetDlg::onUpdate()
{
    QSettings   set;
    QString     ip;
    ip = ui->lineEditIP->text();
    set.setValue("ip",ip);
    if ( FTAPI::Instance()->getSock()->isconnected())
    {
        FTAPI::Instance()->close();
    }else
        FTAPI::Instance()->login(QHostInfo::localHostName().toLocal8Bit().data(),ip.toUtf8().data(),7000);
    MainDialog::Instance()->getFloatDlg()->onSoftUpdate();
}
*/
void QSetDlg::textEdited(const QString &text)
{
    QSettings   set;
    QString     ip;
    ip = ui->lineEditIP->text();
    set.setValue("ip",ip);
}

/**
 * @brief QSetDlg::onCancelClick
 */
void QSetDlg::onCancelClick()
{
    close();
}
