#ifndef DEFINES
#define DEFINES

#include <QString>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QHash>

//中文字符串处理
#define LOCAL(x)    QString::fromLocal8Bit(x)

#ifndef ICON_SIZE
#define ICON_SIZE       40
#endif

#define TASKBAR_HEIGHT  40
#define PADDING         10
#define STR(x)          #x

#define COMPUTER_ICON   ":/ui/computer.png"
#define CONTROL_ICON    ":/ui/control.png"
#define CYCLE_ICON      ":/ui/cycle.png"

#define SELEC_ICON(x) \
    x == LOCAL("我的电脑") ? QPixmap(COMPUTER_ICON) : \
    x == LOCAL("控制面板") ? QPixmap(CONTROL_ICON) : \
    x == LOCAL("回收站")   ? QPixmap(CYCLE_ICON) : QPixmap()

#define         KB      1024
#define         MB      1048576
#define         GB      1073741824

#define         DOCK_WID    600
#define         DOCK_HEI    300

#define         SHARE_MEM_SIZE      1024

#define         Full_Desk       0
#define         New_Panel       1
#define         Simple_Desk     2
#define         Login_Win       3

//动态密码超时时间:60s
#define         CODE_TIMEOUT    60000

#endif // DEFINES

