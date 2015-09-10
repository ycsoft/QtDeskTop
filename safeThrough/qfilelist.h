#ifndef QFILELIST_H
#define QFILELIST_H

#include <QWidget>
#include <QModelIndex>
#include <QCloseEvent>

class QStandardItemModel;
class QTreeView;
class QListWidget;
class QProgressBar;

class QFileList : public QWidget
{
    Q_OBJECT
public:
    explicit QFileList(QWidget *parent = 0);

    void clearList();
    void closeEvent(QCloseEvent *);
signals:
    void    flushFileList();
public slots:
    void    addShareFile(const char *fn);
    void    slotFlushFileList();
    void    listdoubleClick(QModelIndex index);
    void    slotprogress(uint,uint);
    void    btnClick();
protected:
    void    setupUI();
private:
    QListWidget         *h_list;
    QStringList         h_filelist;
    QProgressBar        *h_progress;
    QTreeView           *h_tree;
    QStandardItemModel  *h_model;
};

#endif // QFILELIST_H
