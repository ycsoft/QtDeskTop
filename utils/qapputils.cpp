#include "qapputils.h"
#include "maindialog.h"
#include "utils/defines.h"
#include "skin/iconbutton.h"

#include <QFileInfo>
#include <QFileIconProvider>
#include <QDesktopWidget>
#include <QFile>
#include <QSettings>

QAppUtils::QAppUtils(QObject *parent) : QObject(parent)
{

}

QSize QAppUtils::getScreenSize(int i)
{
    QDesktopWidget desk;
    QRect rt = desk.screenGeometry(i);

    return QSize(rt.width(),rt.height());
}

void QAppUtils::getScreenSize(int &wid, int &hei)
{
    QSize sz = getScreenSize();
    wid = sz.width();
    hei = sz.height();
}

int QAppUtils::getScreenWid(int i)
{
   QSize sz = getScreenSize(i);
   return sz.width();
}

int QAppUtils::getScreenHei(int i)
{
    QSize sz = getScreenSize(i);
    return sz.height();
}

void QAppUtils::getAppList(QHash<QString, QString> &mapapp)
{
    QFile file("app-list.txt");
    int   id[4],count[4],i = 0 , j = 0,indexcount ;

    if ( file.open(QIODevice::ReadOnly) )
    {
        QString line = file.readLine();
        indexcount = line.toInt();
    }
    for ( j = 0 ; j < indexcount; ++j)
    {
        QString tmp = file.readLine();
        QStringList sl = tmp.split(",");
        id[j] = sl[0].toInt();
        count[j] = sl[1].toInt();
        for( i = 0 ; i < count[j]; ++i)
        {
            QString line = file.readLine();
            //少于5个字节不予考虑
            if ( line.length() > 5)
            {
                line = line.trimmed();
                QStringList columns =  line.split("=");
                QString title = columns[0],path = columns[1];

                title = QString::fromLocal8Bit(title.toAscii());
                path = QString::fromLocal8Bit(path.toAscii());
                if ( path.indexOf("::") < 0 )
                {
                QFileInfo   info(path);
                QFileIconProvider  provider;
                QIcon ico = provider.icon(info);
                mapapp[title] = path;
                MainDialog::ref().getAppList().append(title);
                MainDialog::ref().getAppIconPanelByIndex(id[j])->addApp(ico.pixmap(ICON_SIZE,ICON_SIZE)
                                                            ,title,path);
                }else
                {
                    QPixmap pix = SELEC_ICON(title);
                    MainDialog::ref().getAppList().append(title);
                    mapapp[title] = path;
                    MainDialog::ref().getAppIconPanelByIndex(id[j])->addApp(pix
                                                                ,title,path);
                }
            }
        }
    }
}
IconButton *QAppUtils::getCloseIconBtn(QWidget *parent)
{
    QStringList stricon;
    stricon <<":/ui/btn_close_normal.png"
            <<":/ui/btn_close_highlight.png"
            <<":/ui/btn_close_down.png";
    IconButton *closeB = new IconButton(parent,stricon[0],stricon[1],stricon[2]);
    return closeB;
}

