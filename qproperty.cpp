#include "qproperty.h"
#include "skin/navbutton.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QSettings>

#define LOCAL(x) QString::fromLocal8Bit(x)

QProperty::QProperty(QWidget *parent) :
    FramelessWin(parent)
{
    SetupUI();
}

void QProperty::SetupUI()
{
    resize(1000,700);
    QVBoxLayout *vlay = new QVBoxLayout(this);

    //关闭按钮
    QWidget  *topSkin = new QWidget();
    topSkin->setStyleSheet("background-color:QColor(10,10,10)");

    IconButton *closeb = new IconButton(topSkin,":/ui/btn_close_normal.png",":/ui/btn_close_highlight.png",":/ui/btn_close_down.png");
    QHBoxLayout *topLay = new QHBoxLayout(topSkin);

    connect(closeb,SIGNAL(clicked()),this,SLOT(close()));

    //topLay->setMargin(0);
    topLay->addStretch();
    topLay->addWidget(closeb,0,Qt::AlignRight | Qt::AlignTop);

    //当前壁纸

    QSettings   sets;
    QWidget *picwid = new QWidget(this);

    m_lb_pic = new QLabel(this);
    m_lb_pic->setMaximumSize(600,450);
    m_lb_pic->setMinimumSize(600,450);
    m_lb_pic->setStyleSheet(sets.value("desk-style","border-image: url(:/ui/desk.jpg);").toString());

    //IconButton *changeBtn = new IconButton(this,":/ui/btn_normal.png",":/ui/btn_highlight.png",":/ui/btn_down.png");
    NavButton    *changeBtn = new NavButton(this);

    connect(changeBtn,SIGNAL(clicked()),this,SLOT(slot_click()));
    changeBtn->setButtonText(LOCAL("更换壁纸"));
    changeBtn->setMinimumWidth(200);
    //QPushButton  *changeBtn = new QPushButton(this);
    QVBoxLayout *picLay = new QVBoxLayout(picwid);

    picLay->addWidget(m_lb_pic);
    picLay->addWidget(changeBtn,0,Qt::AlignHCenter);

    vlay->addWidget(topSkin);

    vlay->addWidget(picwid,0,Qt::AlignHCenter);

}

QString QProperty::deskStyleFromPath(QString picpath)
{
    QString stype = "border-image:url(" + picpath+");";
    return stype;
}

void QProperty::slot_click()
{
    QString path = QFileDialog::getOpenFileName(this,LOCAL("选择壁纸"),"",LOCAL("图片(*.jpg *.png *.bmp)"));
    if ( path.isEmpty())
        return;
    QString stype = "border-image:url(" + path+");";
    m_lb_pic->setStyleSheet(stype);
    m_desktop_style = stype;

    QSettings   sets;
    sets.setValue("desk-style",stype);

    emit signal_change(stype);
}
