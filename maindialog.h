#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTimerEvent>
#include <QMenu>
#include <QAction>
#include <QMap>
#include <QSystemTrayIcon>
#include <QPixmap>
#include <QTcpSocket>
#include <QList>
#include <QStackedWidget>
#include <QLineEdit>

#include "skin/deskicon.h"
#include "skin/framelesswin.h"

#include "qproperty.h"
#include "panel.h"
#include "qtips.h"
#include "winFactory/qwinfactory.h"

#include "screenOper/qscreenselector.h"
#include "todo/qtodowidget.h"
#include "todo/qtodomanager.h"
#include "todo/qtodocontent.h"

#define     ROW_LIMIT      6
#define     COL_LIMIT      10

namespace Ui {
class MainDialog;
}

class TaskBar;

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    /**
    * 析构时保存桌面上的图标
    * 信息,显示系统任务栏
    */
    ~MainDialog();

    static MainDialog& ref()
    {
        return *m_mainDlg;
    }

    QAppIconPanel * getAppIconPanel()
    {
        return m_appiconpanel;
    }

    QStringList & getAppList()
    {
        return m_applist;
    }
    QStackedWidget *getStackedWidget()
    {
        return m_stacked;
    }
    QAppIconPanel *getAppIconPanelByIndex(int i)
    {
        return dynamic_cast<QAppIconPanel*>(m_stacked->widget(i));
    }
    TaskBar *getTaskBar() const
    {
        return m_task;
    }
    //构建图形界面
    void setUi();
    void setUi2();
    void setUi3();

    //添加新的图标
    void addApp(QString icon,QString txt,QString path = "");
    void addApp(QPixmap &icon,QString txt,QString path = "");

    /**
     * @brief addNewTips
     * 添加新的系统通知附件
     * @param title
     * @param text
     */
    void addNewTipsWidget(Panel *p,QString title, QString text);

public slots:
    //双击桌面图标
    void    dbclick_icon(QString);
    //显示桌面
    void    showDesktop();
    //任务栏单击我的电脑
    void    click_mycomputer();
    /**
     * @brief action_add_app
     * 添加快捷方式
     *
     */
    void    action_add_app();

    /**
     * @brief action_add_notify
     * 添加系统通知
     */
    void    action_add_notify();
    /**
     * @brief action_prop
     * 右键单击属性
     *
     */
    void    action_prop();
    /**
     * @brief switch_simple
     * 切换至精简模式
     */
    void    switch_simple();

    void trayIconActive(QSystemTrayIcon::ActivationReason reason);//托盘

    /**
     * @brief slot_change_desk
     * @param spic
     *更换系统桌面
     *
     */
    void    slot_change_desk(QString spic);

    /**
     * @brief click
     * @param txt
     * 单击任务栏图标
     */
    void    click(QString txt);

    /**
     * @brief addNotify
     *添加通知
     *
     */
    void    addNotify();
    /**
     * @brief connected
     * TCP连接建立
     *
     */
    void    connected();
    /**
     * @brief readyRead
     * 有数据来，可以接收
     */
    void    readyRead();
    /**
     * @brief showMessage
     * 显示托盘信息
     * @param msg : 要显示的提示信息
     */
    void showMessage(QString msg);
    /**
     * @brief popupMsgWin
     * 弹出系统消息通知框
     */
    void popupMsgWin();
    /**
     * @brief showScreens
     * 屏幕选择
     */
    void showScreens();

    /**
     * @brief viewURL
     */
    void viewURL();

    /**
     * @brief showStart
     * 开始菜单
     */
    void showStart();

    /**
     * @brief showToDoManager
     * 事项管理
     */
    void showToDoManager();

    /**
     * @brief showAll
     */
//    void showAll();
//    void showToDo();
//    void showDone();
signals:
    void sigShowMsg(QString);

private:
    /**
     * @brief createTaskBar
     * 创建桌面任务栏
     *
     * @return:
     * 返回任务栏组件
     */
    QWidget *createTaskBar();

    /**
     * @brief addToTask
     * 双击应用程序时，将其图标添加至任务栏
     *
     * @param path
     */
    void  addToTask(QString path);

    /**
     * @brief remoteFromTask
     * @param path
     */
    void  remoteFromTask(QString path);

    /**
     * @brief createMenu
     * 创建右键的弹出菜单
     *
     */
    void    createMenu(QWidget *parent = 0);
    /**
     * @brief timerEvent
     * 定时事件
     *
     * @param evt
     */
    void    timerEvent(QTimerEvent *evt);

    void  keyPressEvent(QKeyEvent *evt);

    void paintEvent(QPaintEvent *evt);

    /**
     * @brief mousePressEvent
     */
    void mousePressEvent(QMouseEvent*);

    /**
     * @brief contextMenuEvent
     * 右键弹出菜单
     *
     * @param evt
     */
    void    contextMenuEvent(QContextMenuEvent *evt);


    /**
     * @brief hideSysTask
     * 隐藏系统任务栏
     *
     */
    void  hideSysTask();

    /**
     * @brief showSysTask
     * 显示系统任务栏
     *
     */
    void  showSysTask();

    /**
     * @brief createTray
     * 创建托盘图标
     *
     */
    void  createTray();

    Ui::MainDialog *ui;

    QHBoxLayout                 *taskLay;
    QVBoxLayout                 *mainLay;
    QGridLayout                 *gridLay;

    QLabel                      *m_lb_time;
    QLabel                      *m_lb_date;

    int                         m_cur_row;
    int                         m_cur_col;
    QMenu                       *m_menu;

    QHash<QString,QString>      m_map_app;
    QHash<QString,DeskIcon*>    m_task_icon;
    QHash<QString,QTips*>       map_tips;
    QProperty                   *m_prop;
    QSystemTrayIcon             *m_tray;
    Panel                       *left_panel;
    QWidget                     *mid_panel;
    Panel                       *right_panel;
    //数据库
    Panel                       *db_panel;
    //大平台
    Panel                       *plat_panel;
    //应用程序
    Panel                       *app_panel;
    //
    QTcpSocket                  *m_sock;
    //
    TaskBar                     *m_task;
    //
    QAppIconPanel               *m_appiconpanel;
    //系统通知窗体
    QSysMessagePanel            *m_msgWin;
    QStringList                 m_applist;
    QScreenSelector             *m_screenSelector;
    QStackedWidget              *m_stacked;
    QLineEdit                   *m_viewEdit;
    QToDoWidget                 *m_todoWidget;
    QTodoManager                *m_todoManager;
    static MainDialog           *m_mainDlg;
public:
    QToDoContent                *m_all;
    QToDoContent                *m_todo;
    QToDoContent                *m_done;
};

#endif // MAINDIALOG_H
