#ifndef QTIPSWIDGET_H
#define QTIPSWIDGET_H

#include "utils/qhfwebview.h"

#include <QWidget>
#include <QDialog>

class QTipsWidget : public QDialog
{
    Q_OBJECT
public:
    explicit QTipsWidget(QWidget *parent = 0);
    void     execJS(const QString &js);
    ~QTipsWidget(){}
signals:

protected:
    void        initUI();
public slots:

private:
    QHFWebView      *m_web;
};

#endif // QTIPSWIDGET_H
