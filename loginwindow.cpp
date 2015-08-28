
//QT includes
#include <QMessageBox>
#include <QTextCodec>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QMovie>
#include <QLabel>
#include <QCheckBox>
#include <QApplication>
//Custom includes
#include "loginwindow.h"
#include "skin/iconbutton.h"
#include "safe/safeping.h"

#include "loginwithsafe.h"

#include "maindialog.h"

Loginwindow::Loginwindow(QWidget *parent) :
    ShadowDlg(parent)
{
    //ui->setupUi(this);
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    this->resize(435,330);
    QWidget *Top = initTopSkin();
    QVBoxLayout *mainLay = new QVBoxLayout();

    mainLay->setSpacing(0);

    mainLay->addWidget(Top);
    QWidget *midw = new QWidget(this);
    midw->setObjectName("midw");
    midw->setStyleSheet("background-color: rgb(173, 215, 241);");
    midw->setLayout( initMiddle());
    //mainLay->addItem(initMiddle());
    mainLay->addWidget(midw);
    setLayout(mainLay);

    QIcon   ico(":/Icon_tray.png");
    setWindowIcon(ico);

   setWindowTitle(LOCAL("登陆"));
   // client = new QXmppClient();

   bool check;


    SafePing    ping(this);
    if ( ping.ConnectToHost())
    {
        m_login_safe = new LoginWithSafe();
        m_login_safe->SetSafePing(&ping);
        connect(m_login_safe,SIGNAL(LoginWithInfo(QString,QString)),this,SLOT(LoginWithInfo(QString,QString)));
        m_login_safe->exec();
    }

}
Loginwindow::~Loginwindow()
{

}


///
/// \brief Loginwindow::slotloginclick
///
///原版：使用MD5算法对用户JID进行加密，使用加密后的串就行登录
///
///现版：不再使用MD5进行加密
///
///修改时间：2015-05-29
///


//Added By X.D Yang
QWidget* Loginwindow::initTopSkin()
{
    QWidget  *topSkin = new QWidget(this);
    topSkin->setMinimumHeight(160);
    IconButton *setb = new IconButton(this,":/ui/btn_set_normal.png",":/ui/btn_set_hover.png",":/ui/btn_set_press.png");
    //IconButton *minb = new IconButton(this,":/ui/btn_mini_normal.png",":/ui/btn_mini_highlight.png",":/ui/btn_mini_down.png");
    IconButton *closeb = new IconButton(this,":/ui/btn_close_normal.png",":/ui/btn_close_highlight.png",":/ui/btn_close_down.png");
    topSkin->setStyleSheet("border-image: url(:/ui/logo-main.png);");

    QHBoxLayout *topLay = new QHBoxLayout();
    topLay->setMargin(0);
    topLay->addStretch();
    topLay->addWidget(setb,0,Qt::AlignRight | Qt::AlignTop);
    //topLay->addWidget(minb,0,Qt::AlignRight | Qt::AlignTop);
    topLay->addWidget(closeb,0,Qt::AlignRight | Qt::AlignTop);
    topSkin ->setLayout(topLay);

    connect(closeb,SIGNAL(clicked()),qApp,SLOT(quit()));

    connect(setb,SIGNAL(clicked()),this,SLOT(SetServer()));


    //connect(minb,SIGNAL(clicked()),this,SLOT(showMinimized()));
    return topSkin;
}

QHBoxLayout* Loginwindow::initMiddle()
{
    QVBoxLayout *photoLay = new QVBoxLayout();
    QLabel *lb_photo = new QLabel(this);
    QMovie  *movie = new QMovie((":/ui/head.gif"));
    movie->setScaledSize(QSize(80,80));
    lb_photo->setMovie(movie);
    movie->start();
    photoLay->addWidget(lb_photo,0,Qt::AlignTop);
    photoLay->addStretch();

    //用户名密码
    m_edit_user = new QLineEdit(this);
    m_edit_pwd  = new QLineEdit(this);
    m_edit_user->setPlaceholderText(LOCAL("用户账号"));
    m_edit_pwd->setPlaceholderText(LOCAL("密码"));
    m_edit_pwd->setEchoMode(QLineEdit::Password);

    m_edit_user->setMinimumWidth(200);
    m_edit_user->setMaximumWidth(200);
    m_edit_pwd->setMinimumWidth(200);
    connect(m_edit_user,SIGNAL(textEdited(QString)),this,SLOT(userChange(QString)));
    connect(m_edit_pwd,SIGNAL(textEdited(QString)),this,SLOT(pwdChange(QString)));

    //提示标签
    QLabel *lb_regusr = new QLabel(LOCAL("注册用户"));
    lb_regusr->setStyleSheet("color: rgb(85, 85, 255);");

    //找回密码
    QLabel *lb_findpwd = new QLabel(LOCAL("找回密码"));
    lb_findpwd->setStyleSheet("color: rgb(85, 85, 255);");
    IconButton *okButton = new IconButton(this,":/ui/button_login_normal.png",":/ui/button_login_hover.png",
                                          ":/ui/button_login_down.png");
    okButton->AddTxtLabel();
    okButton->SetTextStyle("color: rgb(255, 255, 255);font: 75 9pt 'Aharoni';");
    okButton->SetButtonText(LOCAL("登      录"));
    bool bcheck = connect(okButton,SIGNAL(clicked()), this,SLOT(slotloginclick()));
    //Q_ASSERT(bcheck);
    //用户账号输入
    QHBoxLayout  *layUser = new QHBoxLayout();
    layUser->setMargin(0);
    layUser->setSpacing(10);
    layUser->addWidget(m_edit_user,0,Qt::AlignLeft | Qt::AlignTop);
    //layUser->addWidget(lb_regusr);

    //用户密码输入
    QHBoxLayout *layPwd = new QHBoxLayout();
    layPwd->setMargin(0);
    layPwd->setSpacing(10);
    layPwd->addWidget(m_edit_pwd,0,Qt::AlignLeft | Qt::AlignTop);
    //layPwd->addWidget(lb_findpwd);

    //合并用户名密码布局
    QVBoxLayout *inputLay = new QVBoxLayout();
    inputLay->setSpacing(0);
    inputLay->addStretch();
    inputLay->addItem(layUser);
    inputLay->addItem(layPwd);

    //复选框
    QCheckBox *remPwd = new QCheckBox(LOCAL("记住密码"),this);
    QCheckBox *autoLogin = new QCheckBox(LOCAL("自动登录"),this);
    QString   style = "color: rgb(141, 141, 141);";

    remPwd->setStyleSheet(style);
    autoLogin->setStyleSheet(style);

    QHBoxLayout *checkLay = new QHBoxLayout();
    checkLay->setContentsMargins(0,10,0,0);
    checkLay->addWidget(remPwd);
    checkLay->addStretch();
    checkLay->addWidget(autoLogin);
    checkLay->addStretch();
    inputLay->addItem(checkLay);
    //添加按钮
    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->setContentsMargins(0,10,0,0);
    btnLay->addWidget(okButton,0,Qt::AlignLeft | Qt::AlignTop);
    okButton->setMinimumWidth(m_edit_user->width());
    okButton->setMaximumWidth(m_edit_user->width());

    //btnLay->addStretch();
    inputLay->addItem(btnLay);

    //总布局
    QHBoxLayout *contentLay = new QHBoxLayout();
    contentLay->setMargin(20);
    contentLay->setSpacing(20);
    contentLay->addItem(photoLay);
    contentLay->addItem(inputLay);
    return contentLay;
}
void Loginwindow::LoginWithInfo(QString jid, QString pwd)
{
    QString ip = "";
    QString svr = "";
    m_edit_user->setText(jid);
    m_edit_pwd->setText(pwd);
    //client->login(jid,pwd,svr,ip);
}
void Loginwindow::slotloginclick()
{
    MainDialog *main = new MainDialog;
    main->show();
    setVisible(false);
}
