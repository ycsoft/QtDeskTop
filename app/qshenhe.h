#ifndef QSHENHE_H
#define QSHENHE_H

#include "utils/qhfwebview.h"
#include <QDialog>

class QShenhe : public QDialog
{
    Q_OBJECT
public:
    explicit QShenhe(QWidget *parent = 0);

    ~QShenhe();

signals:

protected:
    void    initUI();
public slots:

private:
    QHFWebView  *m_web;
};

#endif // QSHENHE_H
