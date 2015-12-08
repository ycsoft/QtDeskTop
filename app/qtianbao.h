#ifndef QTIANBAO_H
#define QTIANBAO_H

#include "utils/qhfwebview.h"

#include <QDialog>

class QTianBao : public QDialog
{
    Q_OBJECT
public:
    explicit QTianBao(QWidget *parent = 0);
    ~QTianBao();

signals:

protected:
    void    initUI();
public slots:

private:
    QHFWebView  *m_web;
};

#endif // QTIANBAO_H
