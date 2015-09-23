#ifndef QLOGINDESKTOP_H
#define QLOGINDESKTOP_H

#include "login/qfiletrans.h"
#include "utils/qhfwebview.h"

#include <QWidget>
#include <QWebView>

class QLoginDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit QLoginDesktop(QWidget *parent = 0);
    ~QLoginDesktop();
signals:

public slots:
    void    showMain();
    void    addObject();
    void    exitApp();
    void    msgBox(QString title,QString txt);
    void    caLogin(QString host,QString ip);
    void    upLogin(QString usr, QString pwd, QString host,QString ip);
    QStringList readConfig();

    void    onSvrDownloadFinish(const char*, const char*);

    void    connected();
    void    connectedError();
    void    csleep(int millisec);
protected:
    void    initUI();
    void    downloadSvrList();
private:

    QHFWebView                  *m_web;
    QFileTrans                  *m_client;
};

#endif // QLOGINDESKTOP_H
