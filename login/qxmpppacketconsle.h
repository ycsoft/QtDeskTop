#ifndef QXMPPPACKETCONSLE_H
#define QXMPPPACKETCONSLE_H

#include "QXmppLogger.h"

#include <QDialog>
#include <QCloseEvent>

#define     MAX_MESSAGE_SHOW    10240

namespace Ui {
class QXmppPacketConsle;
}

class QXmppPacketConsle : public QDialog
{
    Q_OBJECT

public:
    explicit QXmppPacketConsle(QWidget *parent = 0);

    ~QXmppPacketConsle();
    void closeEvent(QCloseEvent*);
    void returnPressed();

public slots:
    void    logMessage(QXmppLogger::MessageType,QString);
protected:
    void    saveHistory();
private:
    Ui::QXmppPacketConsle *ui;
};

#endif // QXMPPPACKETCONSLE_H
