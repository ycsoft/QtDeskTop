#ifndef QWINFACTORY_H
#define QWINFACTORY_H

#include <QObject>
#include <QList>

#include "uiframe/qnoframewin.h"
#include "sysMsg/qmessagewidgets.h"
#include "sysMsg/qsysmessagepanel.h"
#include "uiframe/qappiconpanel.h"
#include "maindialog.h"
#include "screenOper/qscreenshort.h"
#include "screenOper/qscreenselector.h"
#include "uiframe/qtransparentwin.h"
#include "todo/qtodowidget.h"
#include "uiframe/qsimplemode.h"
#include "login/qlogindesktop.h"
#include "uiframe/qdocker.h"

class QWinFactory : public QObject
{
    Q_OBJECT
public:
    enum WinType {None,MainWin,Widget,Dialog
                  ,NoFrameWin,MsgWidget,MsgPanel
                  ,APPIconPanel,ScreenShort
                  ,ScreenSelector,TransWin
                 ,ToDoWidget};

    QWidget *   createWindow(int type ,QWidget *parent = 0);

    //记录已在桌面显示的系统功能窗体:消息、开始菜单等
    void        appendToShown(QWidget* wid)
    {
        m_shownWidget.push_back(wid);
    }
    void        removeFromShown(QWidget *wid);
    //隐藏窗体
    void        hideAllShownWindow()
    {
        if ( m_shownWidget.empty() )
            return;
        m_shownWidget.back()->hide();
        m_shownWidget.pop_back();
    }


    static QWinFactory & ref();
signals:

public slots:

private:
    explicit QWinFactory(QObject *parent = 0);
    QList<QWidget*>     m_shownWidget;
};

#endif // QWINFACTORY_H
