#include "qpacketparse.h"

#include <QDomDocument>


QPacketParse::QPacketParse(QObject *parent) : QObject(parent)
{
    m_packtype = Unknown;
}
QPacketParse::QPacketParse(const QString &pack, QObject *parent):QObject(parent)
{
    m_packtype = Unknown;
    isValid(pack);
}


bool QPacketParse::isValid(const QString &pack)
{
    int iq_pos = 0,msgpos = 0;

    iq_pos = pack.indexOf("<iq");
    msgpos = pack.indexOf("<message");

    if ( iq_pos < 0 && msgpos < 0)
    {
        return false;
    }else if( iq_pos >= 0 )
    {
        m_packtype = IQ;
    }else
    {
        m_packtype = Message;
    }
    return true;
}
int QPacketParse::prcessCommand(const QString &pack, void **result)
{
    switch ( m_packtype )
    {
    case IQ:
        {
            break;
        }
    case Message:
        {
            return processMsg(pack,result);
        }
    default:
        {
            return None;
            break;
        }
    }
}

int QPacketParse::processMsg(const QString &msg, void **result)
{
    QDomDocument    dom;
    if(!dom.setContent(msg))
    {
        return None;
    }
    QDomElement     root,elem;
    root = dom.firstChildElement("message");
    elem = root.firstChildElement("body");
    if ( elem.isNull())
    {
        return None;
    }
    QString type = elem.attribute("type","");
    if ( type == "sysmsg")
    {
        QString title = elem.attribute("title");
        QString body = elem.lastChild().nodeValue();
        static SystemMsg smsg;
        smsg.title = title;
        smsg.msg = body;

        *result =&smsg;
        return SysMsg;
    }else
    {
        return None;
    }
}
