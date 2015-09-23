#ifndef QPOPTIPS_H
#define QPOPTIPS_H

#include "utils/qhfwebview.h"

#include <QDialog>

class QPopTips : public QDialog
{
    Q_OBJECT
public:
    explicit QPopTips(QWidget *parent = 0);
    void     setTips(const QString &usr, const QString &etti, const QString &data);
    ~QPopTips();
protected:
    void            initUI();
signals:

public slots:

private:
    QHFWebView      *m_web;
};

#endif // QPOPTIPS_H
