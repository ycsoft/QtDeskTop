#ifndef QADDBSAPP_H
#define QADDBSAPP_H

#include "utils/qhfwebview.h"

#include <QWidget>

class QAddBSApp : public QWidget
{
    Q_OBJECT
public:
    explicit QAddBSApp(QWidget *parent = 0);
    ~QAddBSApp(){}


protected:
    void                initUI();
signals:

public slots:
    void                addObject();

    void                okClick();
private:
    QHFWebView          *m_web;

};

#endif // QADDBSAPP_H
