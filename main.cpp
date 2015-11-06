
#include "maindialog.h"
#include "loginwindow.h"
#include "skin/deskicon.h"
#include "qproperty.h"
#include "panel.h"
#include "qaddapplication.h"
#include "qtips.h"

#include "sysMsg/qmessagewidgets.h"
#include "sysMsg/qsysmessagepanel.h"

#include "test/qtest.h"
#include "utils/defines.h"
#include "utils/qapputils.h"
#include "winFactory/qwinfactory.h"
#include "uiframe/qhtmldock.h"
#include "uiframe/qpurecolorbutton.h"
#include "todo/qtodomanager.h"
#include "todo/qtodocontent.h"
#include "data/qtododata.h"
#include "data/qluaconf.h"
#include "jsCore/qjscore.h"
#include "ipc/qipcmemory.h"
#include "uiframe/qhtmltips.h"
#include "jsCore/qtipswidget.h"
#include "app/qaccountmgr.h"

#include <QDebug>
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <QPropertyAnimation>

#include <Windows.h>
#include <ShellAPI.h>
#include <time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("HF-Soft");
    QCoreApplication::setOrganizationDomain("hf.com");
    QCoreApplication::setApplicationName("desk");

//    QDir dir;
//    QString path = dir.currentPath();
//    qDebug()<<"Current Path:"<<path;
//    QString fname = path + QString::fromLocal8Bit("/html/files/播放器.exe");
//    ShellExecuteA(0,"open",fname.toLocal8Bit().data(),NULL,NULL,SW_SHOW);
    MainDialog main;
    main.show();

//    QSysMessagePanel msgpanel;
//    msgpanel.anim_Show();

//    QPropertyAnimation *anim = new QPropertyAnimation(&msgpanel,"pos");
//    anim->setDuration(500);
//    anim->setStartValue(QPoint(1000,0));
//    anim->setEndValue(QPoint(800,0));
//    anim->start();


    return a.exec();
}
