#ifndef QTODOCONTENT_H
#define QTODOCONTENT_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

#include "uiframe/qpurecolorbutton.h"

class QToDoContent : public QWidget
{
    Q_OBJECT
public:
    enum Type{ AllTask,ToDo,Done};
    explicit QToDoContent(QWidget *parent = 0,int type = AllTask);
    void    setTitle(const QStringList &title);
    void    flushData(const QStringList &);
private:
    void    initUI();
    void    resizeEvent(QResizeEvent*);


signals:

public slots:
private:
    QTreeView           *m_tree;
    QStandardItemModel  *m_model;

    QPureColorButton    *m_okBtn;
    QPureColorButton    *m_cancelBtn;

    int                 m_type;
};

#endif // QTODOCONTENT_H
