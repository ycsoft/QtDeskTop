#ifndef QSOFTCENTER_H
#define QSOFTCENTER_H

#include "utils/qhfwebview.h"

#include <QWidget>
#include <QDialog>
#include <QWebFrame>
/**
 * @brief The QSoftCenter class
 * 软件中心功能界面
 */
class QSoftCenter : public QDialog
{
    Q_OBJECT
public:
    explicit QSoftCenter(QWidget *parent = 0);
    static   QSoftCenter* ref()
    {
        if ( m_inst == NULL )
        {
            m_inst = new QSoftCenter(0);
        }
        return m_inst;
    }

    void     runJS(QString js)
    {
        m_web->page()->mainFrame()->evaluateJavaScript(js);
    }


protected:
    void    closeEvent(QCloseEvent *evt);
    void    initUI();
signals:

public slots:
    void    linkCliced(const QUrl&);

    void    registerObject();

private:
    QHFWebView      *m_web;
    QString         m_softinfo;
    static          QSoftCenter *m_inst;
};

#endif // QSOFTCENTER_H
