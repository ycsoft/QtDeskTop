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

#endif // DEFINES

