#include "qtodomanager.h"
#include "utils/qapputils.h"

#include "taskbar.h"
#include "maindialog.h"
#include "winFactory/qwinfactory.h"
#include "skin/iconbutton.h"
#include "utils/qapputils.h"
#include "data/qtododata.h"



#include <QGridLayout>
#include <QRect>
#include <QStackedWidget>

QTodoManager::QTodoManager(QWidget *parent) : QWidget(parent)
{
    initUI();
    //setWindowFlags(Qt::FramelessWindowHint);
    //showFullScreen();
}


void QTodoManager::initUI()
{
    QGridLayout *grid = new QGridLayout(this);
    QWidget *closew = new QWidget(this);
    IconButton *closeB = QAppUtils::ref().getCloseIconBtn(closew);
    QHBoxLayout *hlay = new QHBoxLayout(closew);

    QWidget *tipw = new QWidget(this);
    QVBoxLayout *tiplay = new QVBoxLayout(tipw);
    m_lbtip = new QLabel(tipw);
    tiplay->addWidget(m_lbtip);
    m_lbtip->setText(LOCAL("当前位置>>"));

    hlay->addWidget(closeB);
    connect(closeB,SIGNAL(clicked()),this,SLOT(close()));
    m_stacked =   new QStackedWidget(this);
    m_wid_alldo = new QToDoContent(this);//QWinFactory::ref().createWindow(QWinFactory::Widget);
    m_wid_alldo->setTitle(QStringList()<<LOCAL("所有事项")<<LOCAL("选择"));

    m_wid_todo =  new QToDoContent(this,QToDoContent::ToDo);//QWinFactory::ref().createWindow(QWinFactory::Widget);
    m_wid_todo->setTitle(QStringList()<<LOCAL("待办事项")<<LOCAL("选择"));

    m_wid_done =  new QToDoContent(this,QToDoContent::Done);//QWinFactory::ref().createWindow(QWinFactory::Widget);
    m_wid_done->setTitle(QStringList()<<LOCAL("已办事项")<<LOCAL("选择"));

    m_wid_alldo->flushData(QToDoData::ref().getAll());
    //按钮
    m_allcando = new QPureColorButton(this);
    m_todobtn  = new QPureColorButton(this);
    m_donebtn  = new QPureColorButton(this);

    m_allcando->setButtonText(LOCAL("全部事项"));
    m_todobtn->setButtonText(LOCAL("待办事项"));
    m_donebtn->setButtonText(LOCAL("已办事项"));

    m_allcando->setIndex(ALLTask);
    m_todobtn->setIndex(ToDoTask);
    m_donebtn->setIndex(DoneTask);

    connect(m_allcando,SIGNAL(clicked(int)),this,SLOT(stack_change(int)));
    connect(m_todobtn,SIGNAL(clicked(int)),this,SLOT(stack_change(int)));
    connect(m_donebtn,SIGNAL(clicked(int)),this,SLOT(stack_change(int)));

    m_allcando->setColors(QColor(0,0,100),QColor(0,200,200)
                          ,QColor(0,100,100),QColor(0,150,150));

    m_todobtn->setColors(QColor(0,0,100),QColor(0,200,200)
                          ,QColor(0,100,100),QColor(0,150,150));
    m_donebtn->setColors(QColor(0,0,100),QColor(0,200,200)
                          ,QColor(0,100,100),QColor(0,150,150));

    QStackedWidget *stacked = m_stacked;
    stacked->setContentsMargins(0,0,0,0);
    stacked->addWidget(m_wid_alldo);
    stacked->addWidget(m_wid_todo);
    stacked->addWidget(m_wid_done);

    grid->setSpacing(5);
    grid->setContentsMargins(0,0,0,10);
    grid->addWidget(tipw,0,0,1,1);
    grid->addWidget(closew,0,2,1,1,Qt::AlignRight);
    grid->addWidget(stacked,1,0,1,3);
    grid->addWidget(m_allcando,2,0,1,1);
    grid->addWidget(m_todobtn,2,1,1,1);
    grid->addWidget(m_donebtn,2,2,1,1);

}
void QTodoManager::initUI2()
{
}

void QTodoManager::stack_change(int i)
{
    if ( i >= 0 && i <= 3)
    {
        m_stacked->setCurrentIndex(i);
        switch ( i )
        {
        case ALLTask:{
            m_lbtip ->setText(LOCAL("当前位置 >> ") + LOCAL("全部事项"));
            break;
        }
        case ToDoTask:{
            m_lbtip->setText(LOCAL("当前位置 >> ") + LOCAL("待办事项"));
            m_wid_todo->flushData(QToDoData::ref().getToDo());
            break;
        }
        case DoneTask:
            m_lbtip->setText(LOCAL("当前位置 >> ")+LOCAL("已办事项"));
            m_wid_done->flushData(QToDoData::ref().getDone());
            break;
        }
    }
}
