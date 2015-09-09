#include "maindialog.h"
#include "ui_maindialog.h"

#include "qaddapplication.h"
#include "qproperty.h"
#include "skin/shadowdlg.h"
#include "qtips.h"
#include "addnotifymsg.h"
#include "utils/qapputils.h"
#include "winFactory/qwinfactory.h"
#include "test/qtest.h"
#include "todo/qtodomanager.h"
#include "data/qtododata.h"

#include <QPainter>
#include <QDateTime>
#include <QProcess>
#include <Windows.h>
#include <ShlDisp.h>
#include <QFileInfo>
#include <QFileIconProvider>

#include <QContextMenuEvent>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>

#include <Windows.h>
MainDialog* MainDialog::m_mainDlg = NULL;


MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),m_prop( new QProperty() )
{
    //ui->setupUi(this);
    m_mainDlg = this;
    m_cur_row = 0;
    m_cur_col = 0;
    //setUi2();


    setUi3();
    startTimer(1000);
    this->showFullScreen();
    //this->show();
    connect(m_prop,SIGNAL(signal_change(QString)),this,SLOT(slot_change_desk(QString)));

    //showSysTask();
    //hideSysTask();
    //createTray();

    m_sock = new QTcpSocket(this);

    connect(m_sock,SIGNAL(connected()),this,SLOT(connected()));
    connect(m_sock,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(this,SIGNAL(sigShowMsg(QString)),this,SLOT(showMessage(QString)));

    //连接通行证
    //m_sock->connectToHost("127.0.0.1",5033);

    m_mainDlg = this;
    createTray();

    QAppUtils::ref().getAppList(m_map_app);
    hideSysTask();

}

void MainDialog::addNotify()
{

}
MainDialog::~MainDialog()
{
    showSysTask();
    delete ui;
    delete m_prop;

//    QFile   file("app-list.txt");
//    if ( file.open( QIODevice::WriteOnly))
//    {
//        QStringList keys = m_applist;
//        for ( int i = 0; i < keys.count(); ++i)
//        {
//            QString ctx = keys.at(i) + "=" + m_map_app[keys[i]] + "\n";
//            file.write(ctx.toLocal8Bit().data());
//        }
//        file.close();
//    }
}

void MainDialog::addToTask(QString path)
{
    QFileInfo info(path);
    QFileIconProvider provider;
    QIcon ico = provider.icon(info);
    DeskIcon    *task =new DeskIcon(this,path,DeskIcon::PATH_NAME);

    task->setMaximumWidth(20);
    task->setIconText(path);
    if ( m_task_icon.find(path) == m_task_icon.end())
    {
        taskLay->insertWidget( taskLay->count()-4,task);
        m_task_icon[path] = task;
    }
    connect(task,SIGNAL(click(QString)),this,SLOT(click(QString)));
}

QWidget*    MainDialog::createTaskBar()
{
    TaskBar *task = new TaskBar(this);
    QLineEdit *search = new QLineEdit();
    m_viewEdit = search;
    connect(search,SIGNAL(returnPressed()),this,SLOT(viewURL()));
    search->setStyleSheet("background-color: rgb(207, 207, 207);font: 75 14pt \"Times New Roman\";");
    search->setMinimumWidth(297);
    search->setMaximumWidth(297);
    search->setMinimumHeight(33);
    search->setPlaceholderText(LOCAL("浏览网址"));
    taskLay = new QHBoxLayout(task);

    DeskIcon    *start = new DeskIcon(task,":/ui/start.png",DeskIcon::NO_TEXT);
    DeskIcon    *screens = new DeskIcon(task,":/ui/screens.png",DeskIcon::NO_TEXT);
    DeskIcon    *settings = new DeskIcon(task,":/ui/setting.png",DeskIcon::NO_TEXT);
    DeskIcon    *todo  = new DeskIcon(task,":/ui/govment.png",DeskIcon::NO_TEXT);
    settings->setToolTip(LOCAL("设置"));
    todo->setToolTip(LOCAL("事项管理"));
    connect(todo,SIGNAL(clicked()),this,SLOT(showToDoManager()));

    connect(start,SIGNAL(clicked()),this,SLOT(showStart()));
    connect(screens,SIGNAL(clicked()),this,SLOT(showScreens()));
    connect(settings,SIGNAL(clicked()),this,SLOT(action_prop()));
    screens->setToolTip(LOCAL("窗口视图"));
    start->setToolTip(LOCAL("开始"));
    taskLay->setSpacing(20);
    taskLay->setContentsMargins(0,0,0,0);
    taskLay->addWidget(start,0,Qt::AlignLeft|Qt::AlignVCenter);
    taskLay->addWidget(search);
    taskLay->addWidget(screens,0,Qt::AlignLeft);
    taskLay->addWidget(settings);
    DeskIcon    *home =new DeskIcon(task,":/ui/room.png",DeskIcon::NO_TEXT);
    home->scaled(20,20);
    home->setToolTip(LOCAL("返回系统桌面"));
    connect(home,SIGNAL(clicked()),this,SLOT(showDesktop()));
    taskLay->addStretch();

    DeskIcon  *notify = new DeskIcon(task,":/ui/notify.png",DeskIcon::NO_TEXT);
    notify->setToolTip(LOCAL("通知"));
    notify->setMaximumWidth(30);
    connect(notify,SIGNAL(clicked()),this,SLOT(popupMsgWin()));

    QWidget *timewd = new QWidget(this);
    m_lb_time = new QLabel(timewd);
    m_lb_date = new QLabel(timewd);
    QLabel *lbtime = m_lb_time;
    QLabel *lbdate = m_lb_date;

    timewd->setAttribute(Qt::WA_TranslucentBackground);
    lbtime->setAttribute(Qt::WA_TranslucentBackground);
    lbdate->setAttribute(Qt::WA_TranslucentBackground);

    lbtime->setStyleSheet("color: rgb(255, 255, 255);font: 75 11pt \"Andalus\";");
    lbdate->setStyleSheet("color: rgb(255, 255, 255);font: 75 11pt \"Andalus\";");

    QDateTime  dt = QDateTime::currentDateTime();

    QDate  date = dt.date();
    QTime  time = dt.time();

    QString stime = time.toString("hh:mm:ss");
    QString sdate = date.toString("yyyy/M/d");

    lbtime->setText(stime);
    lbdate->setText(sdate);
    //添加时间
    QVBoxLayout *vlay = new QVBoxLayout(timewd);
    vlay->setSpacing(2);
    vlay->setContentsMargins(0,1,0,1);
    vlay->addWidget(lbtime,0,Qt::AlignHCenter);
    vlay->addWidget(lbdate,0,Qt::AlignHCenter);

    taskLay->addWidget(home,0,Qt::AlignRight);
    taskLay->addWidget(notify,0,Qt::AlignRight);
    taskLay->addWidget(todo,0,Qt::AlignRight);
    taskLay->addWidget(timewd);
    task->setLayout(taskLay);

    //构建通知窗体
    m_msgWin = dynamic_cast<QSysMessagePanel*>(
                QWinFactory::ref().createWindow(QWinFactory::MsgPanel));

    //构建应用选择窗体
    m_screenSelector =(QScreenSelector *)
            QWinFactory::ref().createWindow(QWinFactory::ScreenSelector);
    m_task = task;
    m_task->setMaximumHeight(40);
    return task;
}

void MainDialog::showScreens()
{
    static QScreenSelector *selector = m_screenSelector;
    int height,taskHei,wid,hei;
    Qt::WindowFlags flag = selector->windowFlags();
    QAppUtils::ref().getScreenSize(wid,hei);

    taskHei = m_task->height();
    height = hei - taskHei;
    selector->resize(wid-80,hei/1.5);
    selector->setWindowFlags(flag | Qt::WindowStaysOnTopHint);
    selector->move(0,0);
    selector->setVisible(true);
}

void MainDialog::viewURL()
{
    QString url = m_viewEdit->text();
    if ( url.isEmpty() )
        return;
    ShellExecute(this->winId(),
                 "open",
                 url.toLocal8Bit().data(),
                 NULL,NULL,SW_SHOWNORMAL);
}
void MainDialog::showStart()
{
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

void MainDialog::showToDoManager()
{
    m_todoManager->showFullScreen();
}


void MainDialog::popupMsgWin()
{

    static bool bshowed = false;

    bshowed = !m_msgWin->isVisible();
    int width,height,taskHei,wid,hei;
    Qt::WindowFlags flag = m_msgWin->windowFlags();
    QAppUtils::ref().getScreenSize(wid,hei);


    taskHei = m_task->height();
    height = hei - taskHei;
    width = wid/3.5;
    m_msgWin->resize(QSize(width,height));
    m_msgWin->setWindowFlags( flag | Qt::WindowStaysOnTopHint);
    m_msgWin->move(wid - width,0);
    m_msgWin->setVisible(bshowed);
    if ( bshowed )
    {
        QWinFactory::ref().appendToShown(m_msgWin);
    }else
    {
        QWinFactory::ref().removeFromShown(m_msgWin);
    }

}

void MainDialog::createMenu( QWidget *parent)
{
    m_menu = new QMenu(parent);

    QAction *create = new QAction(LOCAL("添加快捷方式"),parent);
    QAction *changeMode = new QAction(LOCAL("切换精简模式"),parent);
    QAction *prop = new QAction(LOCAL("属性"),parent);
    QAction *exit = new QAction(LOCAL("退出"),parent);

    connect( create, SIGNAL(triggered()),this,SLOT(action_add_app()));
    connect(changeMode,SIGNAL(triggered()),this,SLOT(switch_simple()));
    connect(prop,SIGNAL(triggered()),this,SLOT(action_prop()));
    connect(exit,SIGNAL(triggered()),qApp,SLOT(quit()));

    m_menu->addAction(create);
    m_menu->addAction(changeMode);
    m_menu->addAction(prop);
    m_menu->addSeparator();
    m_menu->addAction(exit);
}

void MainDialog::contextMenuEvent(QContextMenuEvent *)
{
//    QCursor cur = cursor();

//    m_menu->exec( cur.pos());
}

//隐藏系统任务栏

void MainDialog::hideSysTask()
{
    HWND task;
    task = FindWindow("Shell_TrayWnd",NULL);
    ShowWindow(task,SW_HIDE);
}

//显示系统任务栏

void MainDialog::showSysTask()
{
    HWND task;
    task = FindWindow("Shell_TrayWnd",NULL);
    ShowWindow(task,SW_SHOW);
}

//创建托盘图标
void MainDialog::createTray()
{
    m_tray = new QSystemTrayIcon(this);
    QIcon icon(":/ui/desk.ico");
    m_tray->setIcon(icon);
    m_tray->setToolTip(LOCAL("财政桌面"));
    connect(m_tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayIconActive(QSystemTrayIcon::ActivationReason)));
}

void MainDialog::showMessage(QString msg)
{
    m_tray->showMessage(LOCAL("小贴士"),msg);
}

void MainDialog::action_add_app()
{
    QAddApplication add;
    if ( add.exec())
    {
        QString str = add.m_app;
        QString title = add.m_name;
        if ( str.isEmpty() )
            return;
        QFileInfo info(str);
        QString name = info.fileName();
        QPixmap pix = add.getPixmap();
        if ( title.isEmpty() )
            title = name;

        //addApp( add.getPixmap(),title,str);
        QAppIconPanel *iconpanel = dynamic_cast<QAppIconPanel*>(
                    m_stacked->widget( m_stacked->currentIndex() )
                    );
        iconpanel->addApp(pix,title,str);
        m_map_app[title] = str;
        m_applist.append(title);
    }
}

void MainDialog::action_add_notify()
{
    AddNotifyMsg *add = new AddNotifyMsg(this);
    if ( add->exec())
    {
        QString app = add->getTitle();
        addNewTipsWidget(right_panel,app,"");
    }
}

void MainDialog::action_prop()
{
    if (m_prop->exec())
    {
        //QString sheet = m_prop->styleSheet();
    }
}
void MainDialog::switch_simple()
{
    m_stacked->setCurrentIndex(2);
}

void MainDialog::slot_change_desk(QString spic)
{
    QString pic = "QWidget#iconpanel{" +spic+"};";
    m_appiconpanel->setStyleSheet(pic);
}
//从通行证请求认证码，然后认证
void MainDialog::connected()
{
    QString sndstr = "<usrAuth app=\"desktop\" type=\"getcode\"/>";
    m_sock->write(sndstr.toStdString().c_str(),sndstr.toStdString().length());
    m_sock->waitForBytesWritten(3000);
}
void MainDialog::readyRead()
{
    static int times = 0;
    QString str = QString::fromLocal8Bit(m_sock->readAll().data());
    qDebug()<<"Receive:"<<str;
    switch ( times )
    {
    //通行证发来认证码
    case 0:
        ++times;
        break;
    default:
    {
        QString app = str.left( str.indexOf("="));
        QString txt = str.mid(str.indexOf("=")+1,str.length() - str.indexOf("=")-1);
        if ( map_tips.find(app) != map_tips.end())
            addNewTipsWidget(right_panel,app,txt);
        break;
    }
    }
}

void MainDialog::click(QString txt)
{
    ShellExecute(this->winId(),
                 NULL,
                 txt.toLocal8Bit().data(),
                 NULL,NULL,SW_SHOWNORMAL);
    QMessageBox::information(this,"",txt,0);
    hideSysTask();
}

void MainDialog::timerEvent(QTimerEvent *)
{
    QDateTime  dt = QDateTime::currentDateTime();

    QDate  date = dt.date();
    QTime  time = dt.time();

    QString stime = time.toString("hh:mm:ss");
    QString sdate = date.toString("yyyy/M/d");

    m_lb_time->setText(stime);
    m_lb_date->setText(sdate);
}

void MainDialog::addNewTipsWidget(Panel *p,QString title, QString text)
{
    if ( map_tips.find(title) == map_tips.end() )
    {
        QTips *tips = new QTips(this);
        map_tips[title] = tips;
        tips->setTipTitle(title);
        if(!text.isEmpty())
            tips->addNotifyText(text);
        p->addWidget(tips);
    }else
    {
        QTips *tips = map_tips[title];
        tips->setTipTitle(title);
        tips->addNotifyText(text);
    }

}

void MainDialog::addApp(QPixmap &icon, QString txt,QString path)
{
    DeskIcon *app = new DeskIcon(this);

    if ( !path .isEmpty())
        m_map_app[txt] = path;

    app->setIcon(icon);
    app->setIconText(txt);

    connect(app,SIGNAL(dbclick(QString)),this,SLOT(dbclick_icon(QString)));

    gridLay->addWidget(app,m_cur_row,m_cur_col,1,1,Qt::AlignTop | Qt::AlignLeft);

    m_cur_row++;
    if( m_cur_row >= ROW_LIMIT )
    {
        m_cur_row = 0;
        m_cur_col++;
    }
}

void MainDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;

    opt.init(this);

    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void MainDialog::mousePressEvent(QMouseEvent *evt)
{
    QWinFactory::ref().hideAllShownWindow();
}

void MainDialog::keyPressEvent(QKeyEvent *evt)
{
    switch ( evt ->key() )
    {
        case Qt::Key_Escape:
            close();
            break;
    default:
        QDialog::keyPressEvent(evt);
    }
}



void MainDialog::addApp(QString icon, QString txt,QString path)
{
    DeskIcon *app = new DeskIcon(this,icon);

    if ( !path .isEmpty())
        m_map_app[txt] = path;

    app->setIconText(txt);

    connect(app,SIGNAL(dbclick(QString)),this,SLOT(dbclick_icon(QString)));

    gridLay->addWidget(app,m_cur_row,m_cur_col,1,1,Qt::AlignTop | Qt::AlignLeft);

    m_cur_row++;
    if( m_cur_row >= ROW_LIMIT )
    {
        m_cur_row = 0;
        m_cur_col++;
    }

}


///
/// \brief MainDialog::click_mycompute
/// 双击我的电脑
///
void MainDialog::dbclick_icon( QString txt )
{
    hideSysTask();
    if ( txt == LOCAL("我的电脑"))
    {
        ShellExecute(this->winId(),
                     NULL,
                     "::{20D04FE0-3AEA-1069-A2D8-08002B30309D}",
                     NULL,NULL,SW_SHOWNORMAL);
    }
    else if ( txt == LOCAL("控制面板"))
    {
        //.{21EC2020-3AEA-1069-A2DD-08002B30309D}
        ShellExecute(this->winId(),
                     NULL,
                     "::{21EC2020-3AEA-1069-A2DD-08002B30309D}",
                     NULL,NULL,SW_SHOWNORMAL);
    }
    else if ( txt == LOCAL("回收站"))
    {
        //{645FF040-5081-101B-9F08-00AA002F954E}
        ShellExecute(this->winId(),
                     NULL,
                     "::{645FF040-5081-101B-9F08-00AA002F954E}",
                     NULL,NULL,SW_SHOWNORMAL);
    }else
    {
        QString path = m_map_app[txt];
        ShellExecute(this->winId(),
                     NULL,
                     path.toLocal8Bit().data(),
                     NULL,NULL,SW_SHOWNORMAL);
        addToTask(path);
    }
}

void MainDialog::showDesktop()
{
//    CoInitialize(0);

//    IShellDispatch4 *pdisp = NULL;
//    CoCreateInstance(CLSID_Shell,NULL,CLSCTX_ALL,__uuidof(IShellDispatch4),(void**)&pdisp);
//    pdisp->ToggleDesktop();
//    pdisp->Release();
//    CoUninitialize();
//    showSysTask();
    setVisible(false);
    showSysTask();
    m_tray->show();
    emit sigShowMsg(LOCAL("单击我，你就可以返回专有桌面"));
}

void MainDialog::trayIconActive(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        setVisible(true);
        hideSysTask();
        break;
    default:
        break;
    }
}

void MainDialog::click_mycomputer()
{
    ShellExecute(this->winId(),
                 NULL,
                 "::{20D04FE0-3AEA-1069-A2D8-08002B30309D}",
                 NULL,NULL,SW_SHOWNORMAL);
    hideSysTask();
}

void MainDialog::setUi()
{
    QWidget *content = new QWidget(this);

    gridLay = new QGridLayout( content );
    gridLay->setSpacing(40);

    setObjectName("MainDialog");

    QSettings sets;

    QString deskstyle = sets.value("desk-style","").toString();

    if ( deskstyle.isEmpty())
        setStyleSheet("QDialog#MainDialog{border-image: url(./ui/mac-desk.jpg);}");
    else
        setStyleSheet("QDialog#MainDialog{"+deskstyle+"}");

    addApp(":/ui/computer.png",LOCAL("我的电脑"));
    addApp(":/ui/control.png",LOCAL("控制面板"));
    addApp(":/ui/cycle.png",LOCAL("回收站"));

    QFile file("app-list.txt");

    if ( file.open(QIODevice::ReadOnly) )
    {
        while ( !file.atEnd())
        {
            QString line = file.readLine();
            //少于5个字节不予考虑
            if ( line.length() > 5)
            {
                line = line.left( line.length() - 1 );
                QStringList columns =  line.split("=");
                QString title = columns[0],path = columns[1];

                title = QString::fromLocal8Bit(title.toAscii());
                path = QString::fromLocal8Bit(path.toAscii());
                QFileInfo   info(path);
                QFileIconProvider  provider;
                QIcon ico = provider.icon(info);
                addApp(ico.pixmap(40,40),title,path);
            }
        }
        file.close();
    }

    mainLay = new QVBoxLayout(this);
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->addWidget(content);
    mainLay->addStretch();
    mainLay->addWidget( createTaskBar() );
    createMenu();
}

void MainDialog::setUi3()
{
    int wid,hei,px,py;

    QToDoData::ref().appendAll(LOCAL("国库单据")).appendAll(LOCAL("项目拨款"))
                               .appendAll(LOCAL("国库处项目审批"));
    QVBoxLayout *mainLay = new QVBoxLayout(this);
    m_appiconpanel = dynamic_cast<QAppIconPanel*>(
                QWinFactory::ref().createWindow(QWinFactory::APPIconPanel,this)
                );

    QAppIconPanel *panel = dynamic_cast<QAppIconPanel*>
            (QWinFactory::ref().createWindow(QWinFactory::APPIconPanel,this));
    QAppUtils::ref().getScreenSize(wid,hei);

    QSimpleMode *smode = new QSimpleMode(this);

    createTaskBar();
    m_stacked = new QStackedWidget(this);
    m_stacked->addWidget(m_appiconpanel);
    m_stacked->addWidget(panel);
    m_stacked->addWidget(smode);
    m_stacked->setCurrentIndex(0);
    m_stacked->setContentsMargins(0,0,0,0);

    m_appiconpanel->resize(wid,hei - m_task->height());
    mainLay->setSpacing(0);
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->addWidget(m_stacked);
    mainLay->addWidget(m_task);
    createMenu(m_appiconpanel);

    m_appiconpanel->setMenu(m_menu);
    m_todoWidget = dynamic_cast<QToDoWidget*>(
                QWinFactory::ref().createWindow(QWinFactory::ToDoWidget,this));
    px = wid - 200;
    py = hei - m_task->height() - 80;
    m_todoWidget->resize(200,20);
    m_todoWidget->setWindowFlags( m_todoWidget->windowFlags() | Qt::WindowStaysOnTopHint );
    m_todoWidget->move(px,py);
    m_todoWidget->setVisible(false);

    m_todoManager = new QTodoManager();

    m_all = new QToDoContent(0);
    m_all->setWindowTitle(LOCAL("所有事项"));
    m_all->setWindowFlags( m_all->windowFlags() | Qt::WindowStaysOnTopHint );
    m_all->setTitle(QStringList()<<LOCAL("所有事项")<<LOCAL("选择"));
    m_all->flushData(QToDoData::ref().getAll());


    m_todo = new QToDoContent(0,QToDoContent::ToDo);
    m_todo->setWindowTitle(LOCAL("待办事项"));
    m_todo->setTitle(QStringList()<<LOCAL("待办事项")<<LOCAL("选择"));
    m_todo->setWindowFlags( m_todo->windowFlags() | Qt::WindowStaysOnTopHint );

    m_done = new QToDoContent(0,QToDoContent::Done);
    m_done->setWindowTitle(LOCAL("已办事项"));
    m_done->setTitle(QStringList()<<LOCAL("已办事项")<<LOCAL("选择"));
    m_done->setWindowFlags( m_done->windowFlags() | Qt::WindowStaysOnTopHint );

    m_all->setWindowFlags(m_all->windowFlags() | Qt::WindowStaysOnTopHint);
    m_todo->setWindowFlags(m_todo->windowFlags() | Qt::WindowStaysOnTopHint);
    m_done->setWindowFlags(m_done->windowFlags() | Qt::WindowStaysOnTopHint);

//    m_todoManager->m_wid_alldo = m_all;
//    m_todoManager->m_wid_todo = m_todo;
//    m_todoManager->m_wid_done = m_done;
//    m_todoManager->initUI();

    connect(m_todoWidget,SIGNAL(clicked()),this,SLOT(showToDoManager()));
}

//测试用，本函数未正式使用
void MainDialog::setUi2()
{
    QGridLayout *gridLay = new QGridLayout(this);
    gridLay->setMargin(0);
    gridLay->setSpacing(5);
    createMenu();

    setObjectName("MainDialog");
    setStyleSheet("QWidget#MainDialog{border-image: url(./ui/mac-desk.jpg);}");
    left_panel = new Panel(this,Panel::Horiznal);
    right_panel = new Panel(this,Panel::Horiznal);


    db_panel = new Panel(this,Panel::Horiznal);
    db_panel->setObjectName("db_panel");
    db_panel->setRowColLimit(4,3);
    db_panel->setMinimumHeight(100);
    db_panel->addApp(LOCAL("示例库1"),QPixmap("./ui/db.png"));
    db_panel->addApp(LOCAL("示例库2"),QPixmap("./ui/db2.png"));
    db_panel->addApp(LOCAL("示例库1"),QPixmap("./ui/db.png"));
    db_panel->addApp(LOCAL("示例库2"),QPixmap("./ui/db2.png"));

    plat_panel = new Panel(this,Panel::Vertical);
    plat_panel->setObjectName("plat_panel");
    plat_panel->setMargins(10,30,10,120);
    plat_panel->setRowColLimit(3,5);
    plat_panel->setStyleSheet("QWidget#plat_panel{border-image: url(./ui/mac.png);}");
    plat_panel->setMinimumSize(628,412);

    app_panel = new Panel(this,Panel::Horiznal);
    app_panel->setObjectName("app_panel");
    app_panel->setStyleSheet("QWidget#app_panel{border-image: url(./ui/mac-board.png);}");
    app_panel->setMinimumSize(600,100);
    app_panel->setRowColLimit(3,5);
    app_panel->setMargins(10,10,10,10);
    app_panel->addApp(LOCAL("示例应用"),QPixmap("./ui/db2.png"));
    app_panel->addApp(LOCAL("示例应用"),QPixmap("./ui/db.png"));
    app_panel->addApp(LOCAL("示例应用"),QPixmap("./ui/db2.png"));
    app_panel->addApp(LOCAL("示例应用"),QPixmap("./ui/db.png"));


    gridLay->addWidget(left_panel,  0,0,3,1);
    gridLay->addWidget(db_panel,    0,1,1,1);
    gridLay->addWidget(plat_panel,  1,1,1,1);
    gridLay->addWidget(app_panel,   2,1,1,1);
    gridLay->addWidget(right_panel, 0,2,3,1);

    right_panel->setRowColLimit(2,2);

//    right_panel->addWidget(new QTips(right_panel));
//    right_panel->addWidget(new QTips(right_panel));
//    right_panel->addWidget(new QTips(right_panel));
//    right_panel->addWidget(new QTips(right_panel));
//    mid_panel->setLayout(vlay);

    QMenu *right_menu = new QMenu(right_panel);
    QAction *create = new QAction(LOCAL("添加通知"),this);

    connect(create,SIGNAL(triggered()),this,SLOT(action_add_notify()));

    right_menu->addAction(create);

    right_panel->setMenu(right_menu);

}
