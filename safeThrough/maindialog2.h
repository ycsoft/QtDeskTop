#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QMap>
#include <QXmppMessage.h>
#include <QXmppClient.h>
#include <QTimerEvent>

#include "skin/framelesswin.h"

#define     HEART_BEAT      30000


class QFileTrans;
class QXmppPacketConsle;
class FTAPI;
class TCPServer;
class QViewNote;
class QFloatIcon;


namespace Ui {
class MainDialog;
}

class MainDialog : public FramelessWin
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);

    void timerEvent(QTimerEvent*);
    void downloadSvrList();
    virtual void SetupUI();

    QViewNote*      getViewNoteDlg(){return m_viewnote;}
public slots:
    void    caLogin();
    void    loginClick();
    void    exitClick();

    bool    onConfirm(QString info);
    void    onConnect();
    void    onDisconnect();
    void    error(QXmppClient::Error);
    void    onAdvantageClick();

    void    onSvrDownloadFinish(const char*, const char*);

    void    messageReceived(const QXmppMessage &message);

public:
    QFileTrans          *getClient(){return m_client;}
    FTAPI               *getFT() { return m_ft;}
    QFloatIcon          *getFloatDlg() { return m_floatDlg;}
    void                showXmppConsle() ;
    static  MainDialog  *Instance();
    void                decCount() { --m_syscount;}
    void                addCount() { ++m_syscount;}
    void                resetCount() { m_syscount = 0;}
    int                 getCount() { return m_syscount;}
protected:
    void    readConfig();
private:
    Ui::MainDialog *ui;
    static MainDialog           *m_instance;
    QFileTrans                  *m_client;
    QXmppPacketConsle           *m_xmppconsle;
    FTAPI                       *m_ft;
    QPoint                      m_curPos;
    TCPServer                   *m_svrsock;
    QMap<QString,QString>       svr_list;
    qint32                      m_syscount;
    QViewNote                   *m_viewnote;
    QFloatIcon                  *m_floatDlg;

    int                         m_timerID;

};

#endif // MAINDIALOG_H
