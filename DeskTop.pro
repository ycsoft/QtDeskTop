#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T17:14:55
#
#-------------------------------------------------

QT       += core gui network xml webkit
DEFINES += _UNICODE
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeskTop
TEMPLATE = app

SOURCES += main.cpp\
        maindialog.cpp \
    loginwindow.cpp \
    loginwithsafe.cpp \
    skin/framelesswin.cpp \
    skin/iconbutton.cpp \
    skin/loginwin.cpp \
    skin/shadowdlg.cpp \
    skin/tabbutton.cpp \
    safe/safeping.cpp \
    taskbar.cpp \
    skin/deskicon.cpp \
    qaddapplication.cpp \
    qproperty.cpp \
    skin/navbutton.cpp \
    panel.cpp \
    qtips.cpp \
    qtiptxt.cpp \
    addnotifymsg.cpp \
    sysMsg/qsysmessagepanel.cpp \
    utils/qapputils.cpp \
    uiframe/qnoframewin.cpp \
    test/qtest.cpp \
    winFactory/qwinfactory.cpp \
    sysMsg/qmessagewidgets.cpp \
    uiframe/qappiconpanel.cpp \
    screenOper/qscreenselector.cpp \
    screenOper/qsinglescreen.cpp \
    screenOper/qscreenshort.cpp \
    uiframe/qtransparentwin.cpp \
    todo/qtodowidget.cpp \
    uiframe/qpurecolorbutton.cpp \
    todo/qtodomanager.cpp \
    todo/qtodocontent.cpp \
    data/qtododata.cpp \
    data/hfpgsql.cpp \
    uiframe/qsimplemode.cpp \
    login/qlogindesktop.cpp \
    http/qhttpdownload.cpp \
    login/caoper.cpp \
    data/qluaconf.cpp \
    login/qfiletrans.cpp \
    login/session.cpp \
    login/tcpserver.cpp

HEADERS  += maindialog.h \
    ui_maindialog.h \
    loginwindow.h \
    loginwithsafe.h \
    skin/framelesswin.h \
    skin/iconbutton.h \
    skin/loginwin.h \
    skin/shadowdlg.h \
    skin/tabbutton.h \
    safe/safeping.h \
    taskbar.h \
    skin/deskicon.h \
    qaddapplication.h \
    qproperty.h \
    skin/navbutton.h \
    panel.h \
    qtips.h \
    qtiptxt.h \
    addnotifymsg.h \
    sysMsg/qsysmessagepanel.h \
    utils/qapputils.h \
    uiframe/qnoframewin.h \
    test/qtest.h \
    winFactory/qwinfactory.h \
    sysMsg/qmessagewidgets.h \
    utils/defines.h \
    uiframe/qappiconpanel.h \
    screenOper/qscreenselector.h \
    screenOper/qsinglescreen.h \
    screenOper/qscreenshort.h \
    uiframe/qtransparentwin.h \
    todo/qtodowidget.h \
    uiframe/qpurecolorbutton.h \
    todo/qtodomanager.h \
    todo/qtodocontent.h \
    data/qtododata.h \
    data/hfpgsql.h \
    uiframe/qsimplemode.h \
    login/qlogindesktop.h \
    http/qhttpdownload.h \
    login/caoper.h \
    data/qluaconf.h \
    login/qfiletrans.h \
    login/session.h \
    login/tcpserver.h \
    login/CommandParse.hpp \
    login/datatypes.h \
    login/qutil.h

RESOURCES += \
    res.qrc

LIBS += user32.lib shell32.lib ole32.lib

RC_FILE = app.rc
#QMAKE_APP_FLAG += UNICODE
INCLUDEPATH += "D:\Program Files (x86)\LuaJIT-2.0.3\include"
INCLUDEPATH += ".\\rapidjson"
INCLUDEPATH += "E:\Workspace\HF-Soft\libevent-2.0.22-stable\WIN32-Code"
INCLUDEPATH += "E:\Workspace\HF-Soft\libevent-2.0.22-stable\include"
INCLUDEPATH += "D:\PostgreSQL\9.3\include"

DEFINES +=  WIN32_LEAN_AND_MEAN BOOST_ALL_NO_LIB BOOST_SYSTEM_NO_DEPRECATED _WIN32_WINNT=0x0501

INCLUDEPATH += "E:\Workspace\QT\qxmpp-master\src\client"
INCLUDEPATH += "E:\Workspace\QT\qxmpp-master\src\base"
INCLUDEPATH += "E:\swift-2.0\3rdParty\Boost\src"

LIBS += "E:\swift-2.0\3rdParty\Boost\Swiften_Boost.lib"
LIBS += "E:\Workspace\QT\build-qxmpp-unknown-Debug\src\qxmpp_d0.lib"

LIBS += "D:\Program Files (x86)\LuaJIT-2.0.3\lib\lua51.lib"
LIBS += "D:\PostgreSQL\9.3\lib\libpq.lib"



