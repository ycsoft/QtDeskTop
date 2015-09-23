#ifndef QSOFTCENTER_H
#define QSOFTCENTER_H

#include "utils/qhfwebview.h"

#include <QWidget>
#include <QDialog>
/**
 * @brief The QSoftCenter class
 * 软件中心功能界面
 */
class QSoftCenter : public QDialog
{
    Q_OBJECT
public:
    explicit QSoftCenter(QWidget *parent = 0);

protected:
    void    initUI();
signals:

public slots:
    void    linkCliced(const QUrl&);

    void    registerObject();

private:
    QHFWebView      *m_web;
    QString         m_softinfo;
};

#endif // QSOFTCENTER_H
