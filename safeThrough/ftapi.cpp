#include "ftapi.h"
#include "datatypes.h"
#include "mysock.h"

#include <QDebug>

using namespace datatype;
static boost::asio::io_service  sios;


FTAPI* FTAPI::m_instance = NULL;
FTAPI::FTAPI(QObject *parent) :
    QObject(parent)
{
    c_sock = new MySock(sios);
}
/**
 * @brief FTAPI::downloadFile
 * @param filename
 *
 * 从服务器中下载指定文件
 */
void FTAPI::downloadFile(const char *filename)
{
    QString qs_fn = QString::fromLocal8Bit(filename);
    datatype::downloadFile  down;
    QFile *f = new QFile(qs_fn);
    if ( !f->open(QIODevice::WriteOnly))
    {
        f->close();
        return;
    }
    FTAPI::Instance()->getSock()->setHashOffline(qs_fn,f);
    memcpy_s(down.filename,FILE_NAME_LEN,qs_fn.toLocal8Bit().data(),qs_fn.toLocal8Bit().length());
    memcpy_s(down.jid,JID_LEN,"client",JID_LEN);
    FTAPI::Instance()->getSock()->senddata(&down,sizeof(down));
}
/**
 * @brief FTAPI::login
 * @param id  ：登陆时所用的账号名
 * @param host：服务器IP地址
 * @param port：服务器端口
 *
 * 登陆文件传输服务器
 *
 *
 */
void FTAPI::login(const char *id, const char *host, int port)
{

    online  on;
    int     rp = rand()%11;
    port += rp;
    qDebug()<<"Connect to server on port:"<<port;
    on.head.len = htons( PacketLen(on) );
    memset(on.jid,0,JID_LEN);
    memcpy_s(on.jid,JID_LEN,id,strlen(id)+1);
    c_sock->start(host,port);
    if ( c_sock->isconnected())
    c_sock->senddata(&on,sizeof(online));
}
/**
 * @brief FTAPI::close
 *
 * 关闭Socket,结束接收线程
 */
void FTAPI::close()
{
    c_sock->stop();
}

/**
 * @brief FTAPI::rejectFile
 * @param from
 * @param to
 * @param filename
 *
 * 拒绝接收文件
 *
 */
void FTAPI::rejectFile(const char *from, const char *to, const char *filename)
{
    rejectTrans reject;
    reject.head.len = htons(PacketLen(reject));
    memcpy_s(reject.fromjid,JID_LEN,from,JID_LEN);
    memcpy_s(reject.jid,JID_LEN,to,JID_LEN);
    memcpy_s(reject.filename,FILE_NAME_LEN,filename,FILE_NAME_LEN);
    c_sock->senddata(&reject,sizeof(reject));
}

FTAPI::~FTAPI()
{
    if (c_sock)
    {
        sios.stop();
        delete c_sock;
        c_sock = NULL;
    }
    if ( m_instance )
    {
        delete m_instance;
        m_instance = NULL;
    }
}
/**
 * @brief FTAPI::slotAgreeFileTrans
 * @param from
 * @param to
 * @param filename
 *
 * 同意接受文件
 *
 */
void FTAPI::slotAgreeFileTrans(QString from, QString to, QString filename)
{
    QFile file(filename);
    if  ( !file.exists() )
        return;
    if ( !file.open(QIODevice::ReadOnly))
        return;
    uint transed = 0 , total = 0;
    total = file.size();
    char    cfrom[JID_LEN] = {0},
            cto[JID_LEN] = {0},
            cfile[FILE_NAME_LEN] = {0};
    memcpy_s(cfrom,JID_LEN,from.toLocal8Bit().data(),from.length());
    memcpy_s(cto,JID_LEN,to.toLocal8Bit().data(),to.length());
    memcpy_s(cfile,FILE_NAME_LEN,filename.toLocal8Bit().data(),filename.length());

    while( !file.atEnd())
    {
        uchar  buf[DATA_LEN] = {0};
        uint   len = file.read((char*)buf,DATA_LEN);
        transed += len;
        datatype::senddata   sd;
        sd.head.len = htons(PacketLen(sd));
        memcpy_s(sd.filename,FILE_NAME_LEN,cfile,FILE_NAME_LEN);
        memcpy_s(sd.fromjid,JID_LEN,cfrom,JID_LEN);
        memcpy_s(sd.tojid,JID_LEN,cto,JID_LEN);
        sd.transfered = htonl(len);
        sd.total = htonl(total);
        emit signalprogress(transed,total);
        memset(sd.data,0,DATA_LEN);
        memcpy_s(sd.data,DATA_LEN,buf,len);
        senddata(&sd,sizeof(sd));
    }
}
/**
 * @brief FTAPI::senddata
 * @param data：要发送的数据
 * @param len ：发送的字节数
 *
 * 发送数据
 */
void FTAPI::senddata(void *data, int len)
{
    c_sock->senddata(data,len);
}
/**
 * @brief FTAPI::setFile
 * @param fn
 *
 *
 *
 */
void FTAPI::setFile(QString fn)
{
    QFile *file = new QFile(fn);
    if (Upload == m_md)
    {
        if ( !file->exists())
            throw "No Specified File";
        else
        {
            if ( !file->open(QIODevice::ReadOnly) )
                throw "Can not open specified file to read";
            m_file = file;
        }
    }else if( Download == m_md)
    {
        if (!file->open(QIODevice::WriteOnly))
            throw "Can not open specified file to write";
        m_file = file;
    }
}
/**
 * @brief FTAPI::sendFileRequest
 * @param from
 * @param to
 * @param filename
 *
 * 发送文件至指定客户端
 */
void FTAPI::sendFileRequest(const char *from,const char *to, const char *filename)
{
    requestSendFile request;
    request.head.len = htons( PacketLen(request));
    memset(request.filename,0,FILE_NAME_LEN);
    memcpy_s(request.filename,FILE_NAME_LEN,filename,FILE_NAME_LEN);
    memset(request.fromjid,0,JID_LEN);
    memcpy_s(request.fromjid,JID_LEN,from,strlen(from)+1);
    memset(request.jid,0,JID_LEN);
    memcpy_s(request.jid,JID_LEN,to,strlen(to)+1);
    c_sock->senddata(&request,sizeof(request));
}
FTAPI * FTAPI::Instance()
{
    if ( m_instance == NULL )
        m_instance = new FTAPI();
    return m_instance;
}
