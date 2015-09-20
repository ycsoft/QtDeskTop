#include "qappiconpanel.h"

#include "uiframe/qdocker.h"
#include "skin/deskicon.h"
#include "test/qtest.h"
#include "utils/qapputils.h"
#include "utils/defines.h"
#include "uiframe/qhtmldock.h"
#include "winFactory/qwinfactory.h"

#include <QPainter>
#include <QStyleOption>
#include <QStyle>
#include <QSettings>
#include <QContextMenuEvent>



QAppIconPanel::QAppIconPanel(QWidget *parent) : QWidget(parent)
{
    QAppUtils::ref().getScreenSize(m_screenWidth,m_screenHight);

    m_currow = 0;
    m_curcol = 0;

    QSettings sets;
    QString deskstyle = sets.value("desk-style","").toString();
    setObjectName("iconpanel");
    if ( deskstyle.isEmpty())
    {
        setStyleSheet("QWidget#iconpanel{border-image: url(./ui/mac-desk.jpg);}");
    }
    else
    {
        setStyleSheet("QWidget#iconpanel{"+deskstyle+"}");
    }
    m_menu = NULL;

}
void QAppIconPanel::addDock()
{
    int x = (m_screenWidth - DOCK_WID)/2;
    int y = m_screenHight - 150;
    QHtmlDock *dock = new QHtmlDock(this);

    dock->setAttribute(Qt::WA_TranslucentBackground);
    dock->move(x,y);
    dock->show();
}

void QAppIconPanel::addApp(QPixmap &pix,QString title, QString path)
{
    int x,y;
    DeskIcon *dkicon = new DeskIcon(this);

    dkicon->setIcon(pix);

    if ( m_currow > ROW_LIMIT )
    {
        m_currow = 0;
        ++m_curcol;
    }
    m_curcol = (m_curcol >= ROW_LIMIT? 0:m_curcol);
    x = m_curcol * m_screenWidth/ COL_LIMIT + PADDING;
    y = (m_currow++) *m_screenHight / ROW_LIMIT + PADDING;

    if ( y + ICON_SIZE + TASKBAR_HEIGHT + PADDING >= m_screenHight )
    {
        m_currow = 0;
        ++m_curcol;
        x = m_curcol * m_screenWidth/ COL_LIMIT + PADDING;
        y = (m_currow++) *m_screenHight / ROW_LIMIT + PADDING;
    }
    dkicon->resize(ICON_SIZE,ICON_SIZE);
    dkicon->show();
    dkicon->move(x,y);
    dkicon->setIconText(title);
    dkicon->setAppPath(path);

}

void QAppIconPanel::paintEvent(QPaintEvent *)
{
    QPainter    p(this);
    QStyleOption op;

    op.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&op,&p,this);
    if ( m_press )
    {
        p.fillRect(QRect(m_presssPoint,m_movePoint),QColor(80,200,100,50));
    }
}
void QAppIconPanel::contextMenuEvent(QContextMenuEvent *evt)
{
    QCursor cur = cursor();
    if(m_menu)
    {
        m_menu->exec(cur.pos());
    }
}
void QAppIconPanel::mousePressEvent(QMouseEvent *evt)
{
    QWinFactory::ref().hideAllShownWindow();
    if ( evt->button() == Qt::LeftButton )
    {
        m_press = true;
        m_presssPoint = evt->pos();
    }
}
void QAppIconPanel::mouseReleaseEvent(QMouseEvent *)
{
    m_press = false;
    update();
}
void QAppIconPanel::mouseMoveEvent(QMouseEvent *evt)
{
    m_movePoint = evt->pos();
    update();
}
