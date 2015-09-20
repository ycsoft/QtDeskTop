#ifndef QHTMLTIPS_H
#define QHTMLTIPS_H

#include "utils/qhfwebview.h"

#include <QWidget>

class QHtmlTips : public QWidget
{
    Q_OBJECT
public:
    explicit QHtmlTips(QWidget *parent = 0);

protected:
    void        initUI();
signals:

public slots:

private:
    QHFWebView      *m_web;
};

#endif // QHTMLTIPS_H
