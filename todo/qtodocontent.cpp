#include "qtodocontent.h"
#include "utils/defines.h"
#include "skin/iconbutton.h"
#include "utils/qapputils.h"
#include "data/qtododata.h"

#include <QGridLayout>
#include <QSpacerItem>
#include <QTreeWidget>
#include <QResizeEvent>
#include <QDebug>

QToDoContent::QToDoContent(QWidget *parent,int type) : QWidget(parent)
{
    initUI();
    m_type = type;

    connect(m_tree,SIGNAL(clicked(QModelIndex)),this,SLOT(tree_clicked(QModelIndex)));
//    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
}

void QToDoContent::setTitle(const QStringList &title)
{
    int ct = title.count();
    int i = 0;
    m_title = title;

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
    connect(m_okBtn,SIGNAL(clicked()),this,SLOT(ok_clicked()));
    connect(m_cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
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
    m_model->clear();
    setTitle(m_title);
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

void QToDoContent::tree_clicked(const QModelIndex &index)
{
    int r = index.row();
    QStandardItem *item = m_model->item(r,1);
    QStandardItem *item2 = m_model->item(r,0);

    if ( item->checkState() == Qt::Checked )
    {
        qDebug()<<"Checked:";
        QString data = m_model->data( m_model->index(r,0)).toString();
        qDebug()<<data;
        m_taskList.append(data);
        m_taskList.removeDuplicates();

    }else
    {
        qDebug()<<"UnChecked";
    }
}

void QToDoContent::ok_clicked()
{
    switch( m_type )
    {
    case AllTask:
    {
        QToDoData::ref().setToDo(m_taskList);
        m_taskList.clear();
        break;
    }
    case ToDo:
    {
        QToDoData::ref().setDone(m_taskList);
        m_taskList.clear();
        break;
    }
    }
}
