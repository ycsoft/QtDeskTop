
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

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
#include "winFactory/qwinfactory.h"
#include "uiframe/qhtmldock.h"
#include "uiframe/qpurecolorbutton.h"
#include "todo/qtodomanager.h"
#include "todo/qtodocontent.h"
#include "data/qtododata.h"
#include "data/qluaconf.h"
#include <QDebug>

#include <Windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("HF-Soft");
    QCoreApplication::setOrganizationDomain("hf.com");
    QCoreApplication::setApplicationName("desk");

//    QHtmlDock   dock;

//    dock.show();
//    MainDialog main;
//    main.showFullScreen();
//    QDocker dock;
//    dock.show();
    QSoftCenter soft;
    soft.show();
    QLuaConf    conf;
    QStringList     res;
//    qDebug()<<conf.getString("downIP");
//    qDebug()<<conf.getString("serverip");
//    qDebug()<<conf.getString("servername");
//    qDebug()<<conf.getInteger("xmpp_port");
//    QList<QLuaConf::srvconf> res;
//      qDebug()<<conf.getString("usrname");

    return a.exec();
}
