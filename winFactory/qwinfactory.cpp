#include "qwinfactory.h"

#include <QDialog>

QWinFactory::QWinFactory(QObject *parent) : QObject(parent)
{

}

QWidget* QWinFactory::createWindow(int type,QWidget *parent)
{
    switch (type) {
    case None:
        return NULL;
        break;
    case Widget:
        return new QWidget( parent );
    case Dialog:
        return new QDialog( parent );
    case NoFrameWin:
        return new QNoFrameWin( parent );
    case MsgWidget:
        return new QMessageWidgets(parent);
    case MsgPanel:
        return new QSysMessagePanel(parent);
    case APPIconPanel:
        return new QAppIconPanel(parent);
    case MainWin:
        return new MainDialog(parent);
    case ScreenShort:
        return new QScreenShort(parent);
    case ScreenSelector:
        return new QScreenSelector(parent);
    case TransWin:
        return new QTransparentWin(parent);
    case ToDoWidget:
        return new QToDoWidget(parent);
    default:
        break;
    }
}

QWinFactory & QWinFactory::ref()
{
    static QWinFactory factory;
    return factory;
}

void QWinFactory::removeFromShown(QWidget *wid)
{
    m_shownWidget.removeAll(wid);
}
