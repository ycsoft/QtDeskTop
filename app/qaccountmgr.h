#ifndef QACCOUNTMGR_H
#define QACCOUNTMGR_H

#include "utils/qhfwebview.h"

#include <QWidget>
#include <QDialog>
#include <QDebug>

class QAccountMgr : public QDialog
{
    Q_OBJECT
public:
    explicit QAccountMgr(QWidget *parent = 0);

    void        reload();
signals:

protected:
    void                initUI();
public slots:
private:
    QHFWebView          *m_web;
};

#endif // QACCOUNTMGR_H
