#include "qviewnote.h"
#include "qutil.h"
#include "session.h"
#include "maindialog.h"
#include "qsysnotehistory.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

QViewNote::QViewNote(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
}

void QViewNote::setupUI()
{
    setWindowFlags(Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint
                   | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setFocusPolicy(Qt::NoFocus);
    resize(70,70);
    m_label = new QLabel(this);
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->addWidget(m_label);
}

void QViewNote::setText(QString txt)
{
    QFont   font = m_label->font();
    m_label->setStyleSheet("color: rgb(255, 0, 0);");
    font.setBold(true);
    m_label->setFont(font);
    m_label ->setText(txt);
    update();
}

void QViewNote::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton){
        m_currentPos = event->globalPos()- frameGeometry().topLeft();
        event->accept();
    }
}
void QViewNote::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton){
        move(event->globalPos() - m_currentPos );
        event->accept();
    }
}
void QViewNote::paintEvent(QPaintEvent *event)
{
    QPainter  painter(this);
    painter.drawPixmap(0,0,m_pixmap);
}
void QViewNote::leaveEvent(QEvent *event)

{
    setCursor(Qt::ArrowCursor);
}
void QViewNote::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);
}
void QViewNote::mouseDoubleClickEvent(QMouseEvent *event)
{
    MainDialog::Instance()->resetCount();
    QSysNoteHistory *note = new QSysNoteHistory(0);
    hide();
    note->show();
}

void QViewNote::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    update();
}
void QViewNote::moveToRightTop()
{
    int wid = QApplication::desktop()->width();
    int hei = QApplication::desktop()->height();
    int cw = this->width();
    int ch = this->height();
    this->move(wid-120,45);
}

