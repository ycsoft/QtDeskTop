#include "qaddapplication.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileIconProvider>

#define LOCAL(x) QString::fromLocal8Bit(x)

QAddApplication::QAddApplication(QWidget *parent) :
    FramelessWin(parent)
{
    SetupUI();
}

void QAddApplication::SetupUI()
{
    resize(500,300);
    QVBoxLayout *vlay = new QVBoxLayout();

    //关闭按钮
    QWidget  *topSkin = new QWidget(this);
    IconButton *setb = new IconButton(this,":/ui/btn_set_normal.png",":/ui/btn_set_hover.png",":/ui/btn_set_press.png");
    //IconButton *minb = new IconButton(this,":/ui/btn_mini_normal.png",":/ui/btn_mini_highlight.png",":/ui/btn_mini_down.png");
    IconButton *closeb = new IconButton(this,":/ui/btn_close_normal.png",":/ui/btn_close_highlight.png",":/ui/btn_close_down.png");
    QHBoxLayout *topLay = new QHBoxLayout();

    connect(closeb,SIGNAL(clicked()),this,SLOT(close()));
    topLay->setMargin(0);
    topLay->addStretch();
    topLay->addWidget(setb,0,Qt::AlignRight | Qt::AlignTop);
    //topLay->addWidget(minb,0,Qt::AlignRight | Qt::AlignTop);
    topLay->addWidget(closeb,0,Qt::AlignRight | Qt::AlignTop);
    topSkin ->setLayout(topLay);

    m_lb_pic = new QLabel(this);
    m_lb_pic->setAttribute(Qt::WA_TranslucentBackground);
    m_lb_pic->setMinimumSize(50,50);

    QWidget  *picwid = new QWidget(this);
    QHBoxLayout *picLay = new QHBoxLayout(picwid);
    picLay->addStretch();
    picLay->addWidget(m_lb_pic);
    picLay->addStretch();

    QWidget *pathwid = new QWidget(this);
    QLabel *lb = new QLabel(this);
    lb->setText(LOCAL("目标"));
    m_line_path = new QLineEdit(this);
    IconButton *fnd = new IconButton(this,":/ui/Icon_find.png",":/ui/Icon_find_high.png",":/ui/Icon_find.png");

    QHBoxLayout *pathLay = new QHBoxLayout(pathwid);
    pathLay->addWidget(lb);
    pathLay->addWidget(m_line_path);
    pathLay->addWidget(fnd);

    QWidget *namewid = new QWidget(this);

    QHBoxLayout *nameLay = new QHBoxLayout(namewid);
    QLabel *lbname = new QLabel(namewid);
    lbname->setText(LOCAL("名称"));
    m_line_name = new QLineEdit(namewid);
    nameLay->addWidget(lbname);
    nameLay->addWidget(m_line_name);



    QHBoxLayout *btnLay = new QHBoxLayout();
    IconButton *okBtn = new IconButton(this,":/ui/btn_normal.png",":/ui/btn_highlight.png",":/ui/btn_down.png");
    okBtn->SetButtonText(LOCAL("确定"));
    btnLay->addStretch();
    btnLay->addWidget(okBtn);
    btnLay->addStretch();

    vlay->addWidget(topSkin);
    vlay->addStretch();
    vlay->addWidget(picwid);
    vlay->addWidget(pathwid);
    vlay->addWidget(namewid);
    vlay->addItem(btnLay);
    vlay->addStretch();
    setLayout(vlay);

    connect(fnd,SIGNAL(clicked()),this,SLOT(slot_find()));
    connect(okBtn,SIGNAL(clicked()),this,SLOT(slot_ok()));
}

void QAddApplication::slot_ok()
{
    m_name = m_line_name->text();
    accept();
}

void QAddApplication::slot_find()
{
    QString path = QFileDialog::getOpenFileName(this,LOCAL("添加快捷方式"),"",
                                                LOCAL("可添加应用(*.exe *.lnk *.html *hml)"));
    m_app = path;

    if ( !path.isEmpty() )
    {
        m_line_path->setText(path);
        QFileInfo info(path);
        QFileIconProvider provider;
        QIcon icon = provider.icon(info);
        m_pixmap = icon.pixmap(40,40);
        m_lb_pic->setPixmap(m_pixmap);
    }

}
