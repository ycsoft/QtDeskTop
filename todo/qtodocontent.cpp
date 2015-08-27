#include "qtodocontent.h"
#include "utils/defines.h"
#include "skin/iconbutton.h"
#include "utils/qapputils.h"

#include <QGridLayout>
#include <QSpacerItem>
#include <QTreeWidget>
#include <QResizeEvent>

QToDoContent::QToDoContent(QWidget *parent,int type) : QWidget(parent)
{
    initUI();
    m_type = type;
//    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
}

void QToDoContent::setTitle(const QStringList &title)
{
    int ct = title.count();
    int i = 0;

    for ( i = 0 ; i < ct; ++i)
    {
        QStandardItem *item = new QStandardItem(title.at(i));
        m_model->setHorizontalHeaderItem(i,item);
    }
}

void QToDoContent::initUI()
{
    QVBoxLayout *vlay = new QVBoxLayout(this);
    QWidget *centerWidget = new QWidget(this);
    QGridLayout *grid = new QGridLayout(centerWidget);

    m_tree = new QTreeView(centerWidget);
    m_tree->setGeometry(QRect(0,0,400,300));

    m_okBtn = new QPureColorButton(centerWidget);
    m_cancelBtn = new QPureColorButton(centerWidget);
    m_okBtn->setButtonText(LOCAL("确认选择"));
    m_cancelBtn->setButtonText(LOCAL("取消"));
    m_okBtn->setMaximumWidth(80);
    m_cancelBtn->setMaximumWidth(80);
    m_model = new QStandardItemModel(this);
    m_model->setColumnCount(2);
    m_tree->setModel(m_model);

    m_tree->setColumnWidth(0,600);
    grid->addWidget(m_tree,0,0,1,4);
    grid->addWidget(m_okBtn,1,2,1,1);
    grid->addWidget(m_cancelBtn,1,3,1,1);

    vlay->addWidget(centerWidget);
}

void QToDoContent::resizeEvent(QResizeEvent *evt)
{
    QSize sz = evt->size();
    int wid0 = sz.width()*0.85
            ,wid1 = sz.width() * 0.1;
    m_tree->setColumnWidth(0,wid0);
    m_tree->setColumnWidth(1,wid1);
}


void QToDoContent::flushData(const QStringList &data)
{
    int i = 0;

    for ( i = 0 ; i < data.count(); ++i)
    {
        QList<QStandardItem*> row;
        QStandardItem *item = new QStandardItem(data.at(i));
        QStandardItem *check = new QStandardItem();

        item->setIcon(QIcon(":/ui/desk.ico"));

        check->setCheckable(true);
        row<<item<<check;
        m_model->appendRow(row);

    }
}
