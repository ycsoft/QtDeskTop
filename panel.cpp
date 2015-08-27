#include "panel.h"
#include "skin/deskicon.h"
#include "qaddapplication.h"

#include <QFileInfo>
#include <QFileIconProvider>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QSettings>

#include <Windows.h>
#include <ShlDisp.h>

#define LOCAL(x) QString::fromLocal8Bit(x)

Panel::Panel(QWidget *parent, int type):
    FramelessWin(parent),m_menu(NULL)
{
    m_row = 0;
    m_col = 0;
    row_limit = RowCount;
    col_limit = ColCount;
    lay_type = type;
    //setAttribute(Qt::WA_TranslucentBackground);
    SetupUI();
}

Panel::~Panel()
{
    QString on = objectName();
    if ( on.isEmpty())
        return;
    QSettings  sets(on,QSettings::IniFormat);
        for ( int i = 0 ; i < m_app_list.count(); ++i)
        {
            AppConfig config = m_app_list[i];
            sets.setValue(config.title,config.path);
        }
}

void Panel::setMenu(QMenu *menu)
{
    m_menu = menu;
}

void Panel::contextMenuEvent(QContextMenuEvent *evt)
{
    QCursor cur = cursor();
    if ( m_menu )
    {
        m_menu ->exec( cur.pos());
    }
}
void Panel::keyPressEvent(QKeyEvent *evt)
{
    int id = evt->key();
    if ( id == Qt::Key_Escape )
    {
        return;
    }
}

void Panel::SetupUI()
{

    QWidget *wid = new QWidget(this);
    QHBoxLayout *lay = new QHBoxLayout(this);

    m_grid_lay = new QGridLayout(wid);
    m_grid_lay->setSpacing(40);
    lay->addWidget(wid);
    lay->addStretch();
    createMenu();

}

void Panel::setMargins(int left, int top, int right, int bottom)
{
    m_grid_lay->setContentsMargins(left,top,right,bottom);
}

void Panel::addApp(QString title, QPixmap &pix)
{
    DeskIcon *dkicon = new DeskIcon(this);

    dkicon->setTextStyle("color: rgb(0, 0, 127);font: 75 9pt \"Times New Roman\";");
    dkicon->setMaximumWidth(50);
    dkicon->setIcon(pix.scaled(40,40));
    dkicon->setIconText(title);

    if ( lay_type == Vertical )
    {
        m_grid_lay->addWidget(dkicon,m_row++,m_col,1,1,Qt::AlignTop | Qt::AlignLeft);
        if ( m_row >= row_limit)
        {
            m_row = 0;
            ++m_col;
            if ( m_col >= col_limit)
                return;
        }
    }
    else
    {
        m_grid_lay->addWidget(dkicon,m_row,m_col++,1,1,Qt::AlignTop | Qt::AlignLeft);
        if ( m_col >= col_limit)
        {
            m_col = 0;
            ++m_row;
            if ( m_col >= row_limit)
                return;
        }

    }

}

void Panel::paintEvent(QPaintEvent *evt)
{
    QStyleOption opt;

    opt.init(this);

    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void Panel::showDesk()
{
        CoInitialize(0);

        IShellDispatch4 *pdisp = NULL;
        CoCreateInstance(CLSID_Shell,NULL,CLSCTX_ALL,__uuidof(IShellDispatch4),(void**)&pdisp);
        pdisp->ToggleDesktop();
        pdisp->Release();
        CoUninitialize();
}

void Panel::createMenu()
{
    m_menu = new QMenu(this);

    QAction *create = new QAction(LOCAL("添加快捷方式"),this);
    QAction *prop = new QAction(LOCAL("属性"),this);
    QAction *home  = new QAction(LOCAL("显示桌面"),this);
    QAction *exit = new QAction(LOCAL("退出程序"),this);

    connect( create, SIGNAL(triggered()),this,SLOT(action_add_app()));
    connect(prop,SIGNAL(triggered()),this,SLOT(action_prop()));
    connect(exit,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(home,SIGNAL(triggered()),this,SLOT(showDesk()));

    m_menu->addAction(create);
    m_menu->addAction(prop);
    m_menu->addAction(home);
    m_menu->addAction(exit);
}

void Panel::action_add_app()
{
    QAddApplication add;
    if ( add.exec())
    {
        QString str = add.m_app;
        QString title = add.m_name;
        if ( str.isEmpty() )
            return;
        QFileInfo info(str);
        QString name = info.fileName();
        if ( title.isEmpty() )
            title = name;
        addApp(title,str);
    }
}

void Panel::action_prop()
{

}

void Panel::addWidget(QWidget *wid)
{
    if ( lay_type == Vertical )
    {
        m_grid_lay->addWidget(wid,m_row++,m_col,1,1,Qt::AlignTop | Qt::AlignLeft);
        if ( m_row >= row_limit)
        {
            m_row = 0;
            ++m_col;
            if ( m_col >= col_limit)
                return;
        }
    }
    else
    {
        m_grid_lay->addWidget(wid,m_row,m_col++,1,1,Qt::AlignTop | Qt::AlignLeft);
        if ( m_col >= col_limit)
        {
            m_col = 0;
            ++m_row;
            if ( m_col >= row_limit)
                return;
        }

    }
}

void Panel::addApp(QString title, QString path)
{
    QFileInfo   info(path);
    QFileIconProvider provider;
    QIcon icon = provider.icon(info);
    DeskIcon *dkicon = new DeskIcon(this);
    dkicon->setAppPath(path);
    dkicon->setTextStyle("color: rgb(200, 0, 127);font: 75 9pt \"Times New Roman\";");
    dkicon->setMaximumWidth(50);
    dkicon->setIcon(icon.pixmap(40,40));
    dkicon->setIconText(title);

    m_app_map[title] = path;
    AppConfig config;
    config.title = title;
    config.path = path;
    m_app_list.append(config);

    if ( lay_type == Vertical )
    {
        m_grid_lay->addWidget(dkicon,m_row++,m_col,1,1,Qt::AlignTop | Qt::AlignLeft);
        if ( m_row >= row_limit)
        {
            m_row = 0;
            ++m_col;
            if ( m_col >= col_limit)
                return;
        }
    }
    else
    {
        m_grid_lay->addWidget(dkicon,m_row,m_col++,1,1,Qt::AlignTop | Qt::AlignLeft);
        if ( m_col >= col_limit)
        {
            m_col = 0;
            ++m_row;
            if ( m_col >= row_limit)
                return;
        }

    }

}
