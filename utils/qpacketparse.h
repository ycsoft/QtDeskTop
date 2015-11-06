#ifndef QPACKETPARSE_H
#define QPACKETPARSE_H

#include <QObject>


struct SystemMsg
{
    QString title;
    QString msg;
};

/**
 * @brief The QPacketParse class
 *
 * 用于解析XMPP报文，提取出需要的内容
 * 系统通知:
 * <message>
 * <body type="sysmsg" title="xxxxx">
 *
 * </body>
 * </message>
 *
 *
 *
 */

class QPacketParse : public QObject
{
    Q_OBJECT
public:
    enum PackType{ Unknown,IQ,Message};
    enum CmdType{ None, SysMsg };

    explicit
    QPacketParse(QObject *parent = 0);

    QPacketParse(const QString &pack, QObject *parent = 0);

    bool    getPackType() const { return m_packtype;}

    ~QPacketParse(){}

    bool     isValid(const QString &pack);
    int      prcessCommand(const QString &pack,void **result);
signals:
protected:
    int     processMsg(const QString &msg, void** result);
public slots:
private:
    int     m_packtype;
};

#endif // QPACKETPARSE_H
