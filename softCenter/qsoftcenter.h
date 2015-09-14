#ifndef QSOFTCENTER_H
#define QSOFTCENTER_H

#include "utils/qhfwebview.h"

#include <QWidget>
/**
 * @brief The QSoftCenter class
 * 软件中心功能界面
 */
class QSoftCenter : public QWidget
{
    Q_OBJECT
public:
    explicit QSoftCenter(QWidget *parent = 0);

protected:
    void    initUI();
signals:

public slots:

private:
    QHFWebView      *m_web;
};

#endif // QSOFTCENTER_H
