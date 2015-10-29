
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

#include <Windows.h>
#include <ShellAPI.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("HF-Soft");
    QCoreApplication::setOrganizationDomain("hf.com");
    QCoreApplication::setApplicationName("desk");

    MainDialog main;
    main.show();

//    QTipsWidget tips;
//    tips.show();

    return a.exec();
}
