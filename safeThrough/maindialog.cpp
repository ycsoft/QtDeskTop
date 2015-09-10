
#include <QSettings>
#include <QXmppClient.h>
#include <QHostInfo>
#include <QXmppMessage.h>
#include <QDateTime>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QXmlStreamWriter>


#include "maindialog.h"
#include "ui_maindialog.h"

#include "qfiletrans.h"
#include "qfloaticon.h"
#include "session.h"
#include "caoper.h"
#include "qxmpppacketconsle.h"
#include "ftapi.h"
#include "tcpserver.h"
#include "mysock.h"
#include "qsetdlg.h"
#include "qviewnote.h"
#include "confirmdlg.h"

#include "framelesswin2.h"


#ifndef LOCAL(X)
#define LOCAL(X) QString::fromLocal8Bit(X)
#endif


MainDialog *MainDialog::m_instance = NULL;

boost::asio::io_service g_io;

MainDialog::MainDialog(QWidget *parent) :
    FramelessWin(parent),
    ui(new Ui::MainDialog)
{
    //ui->setupUi(this);
    SetupUI();
    setWindowIcon(QIcon(":/UI/app.png"));
    this->setObjectName("MainDlg");
    m_floatDlg = new QFloatIcon(0);

    //this->setStyleSheet("QDialog#MainDlg{border-image: url(:UI/background.png);}");
    m_client = new QFileTrans(this);

    readConfig();
    ui->pushButtonCA->setFocus();
    m_ft = FTAPI::Instance();

    bool bcheck;

    bcheck = connect(m_client,SIGNAL(messageReceived(QXmppMessage)),this,SLOT(messageReceived(QXmppMessage)));
    Q_ASSERT(bcheck);

    bcheck = connect(m_client,SIGNAL(disconnected()),this,SLOT(onDisconnect()));
    Q_ASSERT(bcheck);

    bcheck = connect(ui->pushButtonCA,SIGNAL(clicked()),this,SLOT(caLogin()));
    Q_ASSERT(bcheck);

    bcheck = connect(ui->pushButtonLogin,SIGNAL(clicked()),this,SLOT(loginClick()));
    Q_ASSERT(bcheck);

    bcheck = connect(ui->pushButtonCancel,SIGNAL(clicked()),this,SLOT(exitClick()));
    Q_ASSERT(bcheck);

    bcheck = connect(m_client,SIGNAL(connected()),this,SLOT(onConnect()));
    Q_ASSERT(bcheck);

    bcheck = connect(m_client,SIGNAL(error(QXmppClient::Error)),this,SLOT(error(QXmppClient::Error)));
    Q_ASSERT(bcheck);

    bcheck = connect(ui->commandLinkButton,SIGNAL(clicked()),this,SLOT(onAdvantageClick()));
    Q_ASSERT(bcheck);

    m_xmppconsle = new QXmppPacketConsle(this);
    bcheck = connect(m_client,SIGNAL(logMessage(QXmppLogger::MessageType,QString)),m_xmppconsle,SLOT(logMessage(QXmppLogger::MessageType,QString)));
    Q_ASSERT(bcheck);
    m_instance = this;
    m_svrsock = new TCPServer(g_io,5033,this);
    connect(m_svrsock,SIGNAL(onConfirm(QString)),this,SLOT(onConfirm(QString)));

    QSettings set;
    QString svr = QHostInfo::localHostName();
    QString hostip = set.value("ip",Default_IP).toString();
    if ( !QFile("svrset.ini").exists())
    {
        m_ft->login(svr.toLocal8Bit().data(),hostip.toUtf8().data(),7000);
        downloadSvrList();
    }else
    {
        onSvrDownloadFinish(NULL,NULL);
    }
    m_viewnote = new QViewNote(0);
    m_syscount = 0;
    //

}

void MainDialog::SetupUI()
{
    ui->setupUi(this);
}

/**
 * @brief MainDialog::onDisconnect
 */
void MainDialog::onDisconnect()
{
    QMessageBox::warning(this,LOCAL("警告"),LOCAL("到服务网器的网络连接已断开"),0,0);
    ui->pushButtonCA->setEnabled(true);
    ui->pushButtonLogin->setEnabled(true);
    //修改程序图标
    QPixmap pixmap_on(":/UI/app.png");
    pixmap_on.scaled(80,80);
    QImage image = pixmap_on.toImage();
    QRgb col;
    int gray;
    int width = pixmap_on.width();
    int height = pixmap_on.height();
    for(int i=0; i< width; ++i)
    {
        for(int j = 0; j<height;++j)
        {
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    QPixmap pixoff = pixmap_on.fromImage(image.scaled(80,80));
    m_floatDlg->setPixmap(pixoff);
    //m_floatDlg ->setPixmap();

}

//处理服务端推送的消息
void MainDialog::messageReceived(const QXmppMessage &message)
{
    QXmppElementList    elemlist = message.extensions();
    qint32              count = elemlist.count();
    int                 i = 0;
    QString xml;
    QXmlStreamWriter writer(&xml);

    message.toXml(&writer);

    qDebug()<<"Receive message"<<xml;

    QDomDocument doc;

    if ( !doc.setContent(xml))
        return;
    QDomElement root = doc.documentElement();

    QDomElement elem =  root.firstChildElement("app");

    if ( elem.isNull() )
        return;
    QString app = elem.lastChild().nodeValue();

    elem = root.firstChildElement("sysnote");
    QString msg = elem.lastChild().nodeValue();

    //将消息存入哈希表，以APP名称为键值
    m_svrsock->map_pushlist[app] = msg;
    m_svrsock->pushMessage(app,msg);



/*
    for ( i = 0 ; i < count; ++i)
    {
        QXmppElement    elem = elemlist[i];
        if (elem.tagName().compare("sysnote") == 0)
        {
            QDateTime   time = QDateTime::currentDateTime();
            ++m_syscount;
            QString value ;
            value = message.from() + "["+time.toString("yyyy-MM-dd hh:mm:ss") + "]:\r\n";
            value += elem.value();
            value += "\r\n";
            QFile *f = new QFile("note.dat");
            if ( f->open(QIODevice::Append))
            {
                f->write(value.toLocal8Bit());
                f->flush();
            }
            f->close();
            char buf[128] = {0};
            sprintf(buf,"%d条消息",m_syscount);
            QString note= QString::fromLocal8Bit(buf);
            m_viewnote->setPixmap(QPixmap(":/UI/sign.png").scaled(70,70));
            m_viewnote->setText(note);
            m_viewnote->moveToRightTop();
            m_viewnote->show();
        }
    }
    */
}

/**
 * @brief MainDialog::downloadSvrList
 *
 * 从服务器中下载服务器列表
 *
 */
void MainDialog::downloadSvrList()
{
    QString qs_fn = "svrset.ini";
    QFile *f = new QFile(qs_fn);
    /*
     * 文件已经存在，则不必重复下载，直接进行解析
    */

    if ( f->exists() )
    {
        qDebug()<<"文件已存在，直接读取";
        onSvrDownloadFinish(NULL,NULL);
        return;
    }
    datatype::downloadFile  down;

    if ( !f->open(QIODevice::WriteOnly))
    {
        f->close();
        return;
    }
    FTAPI::Instance()->getSock()->setHashOffline(qs_fn,f);
    bool bcheck = connect(FTAPI::Instance()->getSock(),SIGNAL(finished(const char*,const char*)),this,
            SLOT(onSvrDownloadFinish(const char*,const char*)));
    Q_ASSERT(bcheck);
    memcpy_s(down.filename,FILE_NAME_LEN,qs_fn.toLocal8Bit().data(),qs_fn.toLocal8Bit().length());
    memcpy_s(down.jid,JID_LEN,"client",JID_LEN);
    FTAPI::Instance()->getSock()->senddata(&down,sizeof(down));
}

MainDialog *MainDialog::Instance()
{
    Q_ASSERT( m_instance);
    return m_instance;
}

MainDialog::~MainDialog()
{
    delete ui;
}
void MainDialog::onAdvantageClick()
{
    QSetDlg *setdlg = new QSetDlg(this);
    setdlg->show();
}

void MainDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_curPos = event->globalPos()- frameGeometry().topLeft();
        event->accept();
    }
}
void MainDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton){
        move(event->globalPos() - m_curPos);
        event->accept();
    }
}

void MainDialog::error(QXmppClient::Error)
{
    QMessageBox::warning(this,LOCAL("警告"),LOCAL("出现错误"),0,0);
    ui->pushButtonCA->setEnabled(true);
    ui->pushButtonLogin->setEnabled(true);
}

/**
 * @brief MainDialog::loginClick
 *
 *使用用户名密码进行登录，并将此次登录的信息保存在配置文件中
 */
void MainDialog::loginClick()
{
    QString usr = ui->lineEditUsr->text();
    QString pwd = ui->lineEditPwd->text();
    QString svr = ui->comboBox->currentText();
    QString ip = "127.0.0.1";
    if ( svr_list.contains(svr))
    {
        ip = svr_list[svr];
    }
    ui->pushButtonCA->setEnabled(false);
    ui->pushButtonLogin->setEnabled(false);
    m_client->login(usr,pwd,svr,ip);
    QSettings   set;
    set.setValue("usr",usr);
    set.setValue("pwd",pwd);
    set.setValue("svr",svr);
    //usr = QCryptographicHash::hash(usr.toLocal8Bit(),QCryptographicHash::Md5).toHex();
    QString jid = usr + "@" + svr + "/safe";
    Session::Instance()->setJID(jid);

    Session::Instance()->SetPassWord(pwd);
}
/**
 * @brief MainDialog::caLogin
 *
 *CA证书登录
 */
void MainDialog::caLogin()
{
    ui->pushButtonLogin->setEnabled(false);
    QString         qorigin = CAOper::getOrigin();
    QString         server;
    QString         usr;
    CAOper          oper;
    QString         sign = oper.buildAuthRequest(tr(""),qorigin);
    QString         ip = "127.0.0.1";

    server = ui->comboBox->currentText();
    if (svr_list.contains(server))
    {
        ip = svr_list[server];
    }
    usr = qorigin;
    m_client->login(usr,sign,server,ip,QFileTrans::CA);
    QSettings   set;
    set.setValue("svr",server);
}

void MainDialog::exitClick()
{
    m_client->disconnectFromServer();
    //QApplication::exit(0);
    close();
}
void MainDialog::closeEvent(QCloseEvent *e)
{
    QApplication::exit(0);
}
void MainDialog::timerEvent(QTimerEvent *)
{
    QString pack = "<iq type=\"get\" to=\""+ ui->comboBox->currentText() +"\">" +
            "<query xmlns=\"jabber:iq:version\"/>" +
            "</iq>";
    m_client->sendData(pack.toLocal8Bit());
}

void MainDialog::showXmppConsle()
{
    if (m_xmppconsle)
        m_xmppconsle->exec();
}

/**
 * @brief MainDialog::onConnect
 * 登录成功后显示浮动窗体，并将主窗体隐藏
 *
 */
void MainDialog::onConnect()
{
    hide();
    QSettings set;
    set.setValue("svr",ui->comboBox->currentText());

    m_floatDlg->setPixmap(QPixmap(":/UI/app.png").scaled(80,80));
    m_floatDlg->show();
    m_floatDlg->moveToRightTop();
    Session::Instance()->setHostName(ui->comboBox->currentText());
    /***********************************************************/
    m_timerID = startTimer(HEART_BEAT);
}
/**
 * @brief MainDialog::readConfig
 *
 * 读取应用程序设置
 *
 */
void MainDialog::readConfig()
{
    QSettings   set;
    QString usr = set.value("usr","").toString();
    QString svr = set.value("svr","").toString();
    QString ip  = set.value("ip","").toString();
    QString pwd = set.value("pwd","").toString();
    if (ip.isEmpty())
    {
        ip = "127.0.0.1";
        set.setValue("ip",ip);
    }
    if ( !usr.isEmpty())
        ui->lineEditUsr->setText(usr);
    if ( !svr.isEmpty())
        ui->comboBox->setEditText(svr);
    if ( !pwd.isEmpty())
        ui->lineEditPwd->setText(pwd);
}

void MainDialog::onSvrDownloadFinish(const char *, const char *)
{
    QSettings set("svrset.ini",QSettings::IniFormat);
    QSettings sets;
    QStringList keys = set.allKeys();
    QStringList::iterator it = keys.begin();
    QString domain = sets.value("svr","localhost").toString();
    ui->comboBox->clear();
    while ( it != keys.end())
    {
        QString value = set.value(*it).toString();
        char    cbuf[128] = {0};
        memcpy_s(cbuf,128,it->toAscii().data(),it->toAscii().length());
        QString key = QString::fromLocal8Bit(cbuf);
        svr_list[key] = value;
        ui->comboBox->addItem(key);
        ++it;
    }
    ui->comboBox->setEditText(domain);
}
//确认
bool MainDialog::onConfirm(QString info)
{
    /*
    ConfirmDlg  confirm (NULL,info);
    qDebug()<<"=============Confirm=============";
    if ( confirm.exec() == QDialog::Accepted )
    {
        return true;
    }
    */
    FramelessWin2    frm(0,info);

    frm.exec();
    return true;
}



