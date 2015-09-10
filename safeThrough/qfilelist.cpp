#include "qfilelist.h"
#include "ftapi.h"
#include "mysock.h"
#include "session.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QTextCodec>
#include <QStandardItemModel>
#include <QPushButton>
#include <QTreeView>
#include <QLabel>

#ifndef LOCAL(X)
#define LOCAL(X) QString::fromLocal8Bit(X)
#endif

QFileList::QFileList(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
    bool bcheck;
    bcheck = connect(FTAPI::Instance()->getSock(),SIGNAL(addShareFile(const char*)),
                     this,SLOT(addShareFile(const char*)),Qt::BlockingQueuedConnection);
    bcheck = connect(this,SIGNAL(flushFileList()),this,SLOT(slotFlushFileList()));

    bcheck = connect(h_list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(listdoubleClick(QModelIndex)));
    Q_ASSERT(bcheck);

    bcheck = connect(FTAPI::Instance()->getSock(),SIGNAL(signalprogress(uint,uint)),this,SLOT(slotprogress(uint,uint)));
    Q_ASSERT(bcheck);
}

void QFileList::listdoubleClick(QModelIndex index)
{
    QString qs_fn = index.data().toString();
    char    cfile[FILE_NAME_LEN] = {0};
    datatype::downloadFile  down;
    QFile *f = new QFile(qs_fn);
    if ( !f->open(QIODevice::WriteOnly))
    {
        f->close();
        return;
    }
    FTAPI::Instance()->getSock()->setHashOffline(qs_fn,f);
    memcpy_s(down.filename,FILE_NAME_LEN,qs_fn.toLocal8Bit().data(),qs_fn.toLocal8Bit().length());
    memcpy_s(down.jid,JID_LEN,"client",JID_LEN);
    FTAPI::Instance()->getSock()->senddata(&down,sizeof(down));
}
void QFileList::slotprogress(uint done, uint total)
{
    h_progress->setMaximum(total);
    h_progress->setValue(done);
    if ( done >= total)
    {
        QMap<int,QVariant>  map;
        QModelIndex index = h_tree->currentIndex();
        QLabel *lb = new QLabel(this);
        lb->setText(LOCAL("已安装"));
        h_tree->setIndexWidget(index,lb);
        h_tree->setEnabled(true);
    }
}

void QFileList::setupUI()
{
    h_list = new QListWidget(this);
    h_list->hide();
    h_progress = new QProgressBar(this);
    h_progress->setVisible(false);

    h_tree = new QTreeView(this);
    h_tree->setMouseTracking(true);
    h_tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    h_tree->setAllColumnsShowFocus(true);
    h_model = new QStandardItemModel(h_tree);

    h_model->setColumnCount(2);
    h_model->setHeaderData(0,Qt::Horizontal,LOCAL("软件名称"));
    h_model->setHeaderData(1,Qt::Horizontal,LOCAL("操作"));
    h_tree->setModel(h_model);

    h_tree->setColumnWidth(0,400);
    h_tree->setColumnWidth(1,110);

    h_tree->setDragEnabled(true);
    h_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->setSpacing(0);
    vlay->setMargin(0);
    vlay->addWidget(h_tree);
    //vlay->addWidget(h_list);
    //vlay->addWidget(h_progress);
    resize(520,500);

    setWindowTitle(LOCAL("可下载软件"));
    h_tree->setObjectName("tree");
    h_tree->setStyleSheet("QTreeView#tree{border-image: url(:UI/background.png);}");
    QFont ft = h_tree->font();
    ft.setBold(true);
    ft.setWeight(ft.weight() + 2);
    h_tree->setFont(ft);
    setWindowIcon(QIcon(":/UI/app.png"));
}

void QFileList::btnClick()
{
    QPoint pos = this->cursor().pos();
    QProgressBar *progress = new QProgressBar(this);
    h_tree->setEnabled(false);
    h_progress = progress;
    QModelIndex btnindex = h_tree->currentIndex();
    int row = btnindex.row();
    h_tree->setIndexWidget(btnindex,progress);
    QModelIndex nameindex = h_model->index(row,0);
    QString filename = nameindex.data().toString();
    datatype::downloadFile  down;
    QFile *f = new QFile(filename);
    if ( !f->open(QIODevice::WriteOnly))
    {
        f->close();
        return;
    }
    FTAPI::Instance()->getSock()->setHashOffline(filename,f);
    memcpy_s(down.filename,FILE_NAME_LEN,filename.toLocal8Bit().data(),filename.toLocal8Bit().length());
    memcpy_s(down.jid,JID_LEN,Session::Instance()->getHostName().toLocal8Bit().data(),
             Session::Instance()->getHostName().toLocal8Bit().length());
    FTAPI::Instance()->getSock()->senddata(&down,sizeof(down));
}

void QFileList::clearList()
{
    h_list->clear();
    h_filelist.clear();
}
void QFileList::slotFlushFileList()
{
    h_list->clear();
    QStringList::iterator  iter = h_filelist.begin();
    for ( ;iter != h_filelist.end(); ++iter )
    {
        QListWidgetItem *item = new QListWidgetItem(h_list);
        item->setText(*iter);
        h_list->addItem(item);
    }
}

void QFileList::addShareFile(const char* fn)
{
    QStringList list = FTAPI::Instance()->getSock()->getFileList();
    QStringList::iterator  iter = list.begin();
    list.removeDuplicates();
    /*
    h_list->clear();
    for ( ;iter != list.end(); ++iter )
    {
        QListWidgetItem *item = new QListWidgetItem(h_list);
        item->setText(*iter);
        h_list->addItem(item);
    }
    */
    h_model->removeRows(0,h_model->rowCount());
    int irow = 0;
    for ( ;iter != list.end(); ++iter )
    {
       QList<QStandardItem*> row;
       QStandardItem *itname = new QStandardItem(*iter);
       QIcon    ico(":/UI/app2.png");
       itname->setIcon(ico);
       row<<itname<<new QStandardItem("");
       h_model->appendRow(row);
       QPushButton *btn =  new QPushButton(LOCAL("安装"),this);
       connect(btn,SIGNAL(clicked()),this,SLOT(btnClick()));
       btn->setMaximumWidth(50);
       btn->setMaximumHeight(20);
       h_tree->setIndexWidget(h_model->index(irow,1),btn);

       ++irow;
    }

}
void QFileList::closeEvent(QCloseEvent *e)
{
    hide();
    e->ignore();
}
