#include "addnotifymsg.h"
#include "ui_addnotifymsg.h"

AddNotifyMsg::AddNotifyMsg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNotifyMsg)
{
    ui->setupUi(this);

    setWindowTitle(QString::fromLocal8Bit("添加通知"));

    ui->comboBox->addItem(QString::fromLocal8Bit("chen"));
    ui->comboBox->addItem(QString::fromLocal8Bit("国库集中支付"));
    ui->comboBox->addItem(QString::fromLocal8Bit("县级版"));

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(click()));
}

AddNotifyMsg::~AddNotifyMsg()
{
    delete ui;
}

void AddNotifyMsg::click()
{
    m_app = ui->comboBox->currentText();
    accept();
}
