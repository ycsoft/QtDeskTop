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
    uiframe/qdocker.cpp \
    uiframe/qhtmldock.cpp \
    utils/qhfwebview.cpp \
    softCenter/qsoftcenter.cpp \
    jsCore/qjscore.cpp \
    utils/qapparg.cpp \
    ipc/qipcmemory.cpp \
    uiframe/qhtmltips.cpp \
    uiframe/qpoptips.cpp \
    login/tcpserver.cpp \
    jsCore/qtipswidget.cpp \
    app/qaccountmgr.cpp

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
    login/CommandParse.hpp \
    login/datatypes.h \
    login/qutil.h \
    uiframe/qdocker.h \
    uiframe/qhtmldock.h \
    utils/qhfwebview.h \
    softCenter/qsoftcenter.h \
    jsCore/qjscore.h \
    utils/qapparg.h \
    ipc/qipcmemory.h \
    uiframe/qhtmltips.h \
    uiframe/qpoptips.h \
    login/tcpserver.h \
    jsCore/qtipswidget.h \
    app/qaccountmgr.h

RESOURCES += \
    res.qrc

LIBS += user32.lib shell32.lib ole32.lib

RC_FILE = app.rc
#QMAKE_APP_FLAG += UNICODE
INCLUDEPATH += "F:\LuaJIT-2.0.4\src"
INCLUDEPATH += ".\\rapidjson"
#INCLUDEPATH += "E:\Workspace\HF-Soft\libevent-2.0.22-stable\WIN32-Code"
#INCLUDEPATH += "E:\Workspace\HF-Soft\libevent-2.0.22-stable\include"
INCLUDEPATH += "D:\Program Files\PostgreSQL\8.3\include"

DEFINES +=  WIN32_LEAN_AND_MEAN #BOOST_ALL_NO_LIB BOOST_SYSTEM_NO_DEPRECATED _WIN32_WINNT=0x0501

INCLUDEPATH += "F:\C-C++\HF-Soft\qxmpp\qxmpp-master\src\client"
INCLUDEPATH += "F:\C-C++\HF-Soft\qxmpp\qxmpp-master\src\base"
INCLUDEPATH += "F:\C-C++\boost_1_59_0\boost_1_59_0"

#LIBS += "E:\swift-2.0\3rdParty\Boost\Swiften_Boost.lib"

LIBS += "F:\C-C++\boost_1_59_0\boost_1_59_0\stage\lib\libboost_system-vc100-mt-gd-1_59.lib"
LIBS += "F:\C-C++\boost_1_59_0\boost_1_59_0\stage\lib\libboost_date_time-vc100-mt-gd-1_59.lib"
LIBS += "F:\C-C++\boost_1_59_0\boost_1_59_0\stage\lib\libboost_regex-vc100-mt-gd-1_59.lib"
LIBS += "F:\C-C++\boost_1_59_0\boost_1_59_0\stage\lib\libboost_thread-vc100-mt-gd-1_59.lib"
LIBS += "F:\C-C++\boost_1_59_0\boost_1_59_0\stage\lib\libboost_chrono-vc100-mt-gd-1_59.lib"


LIBS += "F:\qxmpp\build-qxmpp-Desktop_Qt_4_8_6-Debug\src\qxmpp_d0.lib"

LIBS += "F:\LuaJIT-2.0.4\lib\lua51.lib"
LIBS += "D:\Program Files\PostgreSQL\8.3\lib\libpq.lib"




