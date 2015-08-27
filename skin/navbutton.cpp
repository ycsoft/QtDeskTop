#include "navbutton.h"

#include <QHBoxLayout>
#include <QPainter>

NavButton::NavButton(QWidget *parent) :
    QPushButton(parent),m_menu(NULL)
{
    setMinimumHeight(60);
    lb_txt = new QLabel(this);
    lb_txt->setAttribute(Qt::WA_TranslucentBackground);
    lb_txt->setStyleSheet("font: 75 15pt \"Times New Roman\";color: rgb(0, 0, 0);");
    lb_txt->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    setAttribute(Qt::WA_TranslucentBackground);
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    lay->addWidget(lb_txt,0,Qt::AlignHCenter);
    m_status = Normal;

    setAttribute(Qt::WA_TranslucentBackground);
}

NavButton::NavButton(QWidget *parent, QString icon, QString txt):
    QPushButton(parent),m_icon_path(icon),m_txt(txt),m_menu(NULL)
{

    setMinimumHeight(60);

    lb_pic = new QLabel(this);
    lb_txt = new QLabel(this);

    lb_pic->setAttribute(Qt::WA_TranslucentBackground);
    lb_pic->setPixmap( QPixmap(icon));
    lb_pic->setMaximumWidth(40);

    lb_txt->setAttribute(Qt::WA_TranslucentBackground);
    lb_txt->setStyleSheet("font: 75 15pt \"Times New Roman\";color: rgb(0, 0, 0);");
    lb_txt->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    lb_txt->setText(txt);

    setAttribute(Qt::WA_TranslucentBackground);
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setSpacing(5);
    lay->addStretch();
    lay->addWidget(lb_pic,0,Qt::AlignLeft | Qt::AlignVCenter);
    lay->addWidget(lb_txt,0,Qt::AlignHCenter);
    lay->addStretch();

    m_status = Normal;

    setAttribute(Qt::WA_TranslucentBackground);
}


void NavButton::setStatus(Status st)
{
    Q_ASSERT( st >= 0 && st <= 2);
    m_status = st;
    update();
}

void NavButton::setButtonText(QString txt)
{
    lb_txt->setText(txt);
}

void NavButton::setTextStyle(QString style)
{
    lb_txt->setStyleSheet(style);
}


void NavButton::enterEvent(QEvent *evt)
{
    setStatus(High);
}

void NavButton::leaveEvent(QEvent *evt)
{
    setStatus(Normal);

}

void NavButton::mousePressEvent(QMouseEvent *evt)
{
    if ( evt->button() == Qt::LeftButton )
    {
        setStatus(Down);
        emit clicked();
        if ( m_menu)
        {
            QRect rt = rect();
            QPoint  pt(rt.width()/3,rt.height());

            m_menu->show();
            m_menu->move(mapToGlobal(pt));
            //m_menu->exec( evt->pos() );
        }

    }
}

void NavButton::mouseReleaseEvent(QMouseEvent *evt)
{
    setStatus(High);
}

void NavButton::paintEvent(QPaintEvent *evt)
{

    //QPushButton::paintEvent(evt);
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing,true);
    if ( m_status == Normal)
    {
//        QBrush brush(QColor(0,0,0,50));
//        paint.setBrush(brush);
//        paint.drawRoundRect(rect());
//        //paint.fillRect(rect(),QBrush(QColor(0,0,0,100)));

    }else if( m_status == High)
    {
        QBrush brush(QColor(0,0,129,50));
        paint.setBrush(brush);
        paint.setPen(Qt::NoPen);
        //paint.drawRoundRect(rect(),10,10);
        paint.drawRoundedRect(rect(),30,30);
        //paint.drawEllipse(rect());
    }else
    {
        QBrush brush(QColor(0,100,0,100));
        paint.setBrush(brush);
        paint.setPen(Qt::NoPen);
        paint.drawRoundedRect(rect(),10,10);
        //paint.drawEllipse(rect());
    }


}
