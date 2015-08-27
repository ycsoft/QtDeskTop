#include "qappiconpanel.h"

#include "skin/deskicon.h"
#include "test/qtest.h"
#include "utils/qapputils.h"
#include "utils/defines.h"

#include <QPainter>
#include <QStyleOption>
#include <QStyle>
#include <QSettings>



QAppIconPanel::QAppIconPanel(QWidget *parent) : QWidget(parent)
{
    QAppUtils::ref().getScreenSize(m_screenWidth,m_screenHight);

    m_currow = 0;
    m_curcol = 0;

    QSettings sets;
    QString deskstyle = sets.value("desk-style","").toString();
    setObjectName("iconpanel");
    if ( deskstyle.isEmpty())
        setStyleSheet("QWidget#iconpanel{border-image: url(./ui/mac-desk.jpg);}");
    else
        setStyleSheet("QWidget#iconpanel{"+deskstyle+"}");

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
}
