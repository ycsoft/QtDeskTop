
#include <QString>
#include <QDebug>
#include <QFile>

#include "tcpserver.h"
#include "maindialog.h"
#include "confirmdlg.h"

#define  MAX_MESSAGE_LENGTH 1024


TCPServer::TCPServer(asio::io_service &ios, int port, QWidget *parent):io_(ios), \
    acceptor_(ios,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
{
    buf_ = new byte[MAX_MEM];
    if ( NULL == buf_)
        throw "stack overflow";
    start();
    run();
    qRegisterMetaType<QList<QString>>("QList<QString>");
    //consle_ = ConsleFactory::instance( PacketConsle::SOCK );
    //connect(this,SIGNAL(onInit(QString)),parent,SLOT(onInitSock(QString)));
    //connect(this,SIGNAL(onNewConnect(QString)),parent,SLOT(onNewConnect(QString)));
    //connect(this,SIGNAL(onConfirm(QList<QString>)),parent,SLOT(onConfirm(QList<QString>)),Qt::BlockingQueuedConnection);
    //connect(this,SIGNAL(onRecvData(QString)),parent,SLOT(onRecvData(QString)));
    //connect(this,SIGNAL(onSendData(QString)),parent,SLOT(onSendData(QString)));
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //connect(this,SIGNAL(onSendRawData(QString)),consle_,SLOT(onSendPacket(QString)));
    //connect(this,SIGNAL(onRecvData(QString)),consle_,SLOT(onRecvPacket(QString)));
    //connect(consle_,SIGNAL(sendRawData(QString)),this,SLOT(sendRawData(QString)));
    //emit onInit(QString("Init OK"));

}
TCPServer::~TCPServer()
{
    qDebug()<<"Sock Server Release Resource";
    io_.stop();
    if (buf_)
    {
        delete [] buf_;
        buf_ = NULL;
    }
}

void TCPServer::start()
{
    qDebug()<<"Local socket server started!";
    socket_pointer  sock(new tcpsocket(io_));
    acceptor_.async_accept(*sock,boost::BOOST_BIND(&TCPServer::handle_accept,this,boost::asio::placeholders::error,sock));
}
XMLNSList TCPServer::getXmlnsList()
{
    return xmlns_list_;
}
void TCPServer::handle_accept(const system::error_code &ec, socket_pointer sock)
{
    if ( ec )
    {
       return;
    }
    qDebug()<<"New Client Accepted";
    //std::cout<<"accept:"<<sock->remote_endpoint().address()<<endl;
    memset(buf_,0,MAX_MEM);
    sock->async_receive(asio::buffer(buf_,MAX_MEM),boost::bind(&TCPServer::handle_read,this,asio::placeholders::error,sock));
    socklist_.push_back(sock);

    start(); //继续接受连接
    emit onNewConnect(QString::fromLocal8Bit("已接受一个新的连接"));
}
void TCPServer::handle_write(const system::error_code &ec, socket_pointer sock)
{
    QString str = QString::fromAscii((const char*)buf_);
    //onSendData(str);
    QFile fd("log.txt");
    fd.open(QIODevice::Append);
    fd.write("In:");
    fd.write((const char*)buf_);
    fd.write("\r\n");
    fd.close();
    onSendRawData(str);
    memset(buf_,0,MAX_MEM);
    sock->async_receive(asio::buffer(buf_,MAX_MEM),boost::bind(&TCPServer::handle_read,this,asio::placeholders::error,sock));
}
void TCPServer::handle_read(const system::error_code &ec, socket_pointer sock)
{
    if ( ec )
    {
        return;
    }
    static char ccc[128] = "";
    memcpy(ccc,buf_,128);
    int ret = 0; //解析命令类型
    QList<QString> list;
    QString qstr = QString::fromAscii((const char*)(buf_));
    onRecvData(qstr);
    qDebug()<<"SockServer: Received New Data:"<<ccc;

    QString  result;
    //sock->async_receive(asio::buffer(buf_,MAX_MEM),boost::bind(&TCPServer::handle_read,this,asio::placeholders::error,sock));
    ret = CommandParse::parsegetAuth(qstr,result);
    if(ret == 6)
    {
        map_sock[Session::Instance()->getAppName()] = sock;
        memset(ccc,0,128);
        memcpy(ccc,result.toLocal8Bit().data(),result.toLocal8Bit().length());
        sock->async_send(asio::buffer(ccc,strlen(ccc)+1),
                         boost::bind(&TCPServer::handle_write,
                         this,asio::placeholders::error,sock));

        return;
    }

    //应用请求借助通行证进行登录
    QString info;
    ret = CommandParse::parsePing(ccc,info);
    if ( ret == CMD_PING )
    {
        Session::Instance()->SetConfirmed(false);
        onConfirm(info);
        int times = 0;
        while( !Session::Instance()->GetConfirmed() )
        {
            times++;
            Sleep(500);
            if ( times >= 100)
                return;
        }
        qDebug()<<"Confirm over";
        char resp[512] = {0};
        QString jid,pwd;
        jid = Session::Instance()->getJID();
        pwd = Session::Instance()->GetPassWord();
        if ( pwd.isEmpty() )
            pwd = jid;
        sprintf(resp,"<pong id=\"%s\" pwd=\"%s\"/>",jid.toLocal8Bit().data(),pwd.toLocal8Bit().data());
        qDebug()<<resp;
        sock->async_send(asio::buffer(resp,strlen((const char*)resp)+1),
                         boost::bind(&TCPServer::handle_write,
                         this,asio::placeholders::error,sock));
        return;

    }
    //使用动态密码进行验证
    ret = CommandParse::parseLogin(qstr,result);
    if ( ret == 1)
    {
        map_sock[Session::Instance()->getAppName()] = sock;
        memset(ccc,0,128);
        memcpy(ccc,result.toLocal8Bit().data(),result.toLocal8Bit().length());
        sock->async_send(asio::buffer(ccc,strlen(ccc)+1),
                         boost::bind(&TCPServer::handle_write,
                         this,asio::placeholders::error,sock));

    }
    ret = CommandParse::parseCmd(qstr,list);
    if ( CMD_START == ret) // 用户首次发送的验证数据
    {
        memset(buf_,0,MAX_MEM);
        bool ret = onConfirm(list);
        if ( ret ) //允许应用进行连接
        {
            strcpy((char*)buf_,"Yes");
            // 及时更新客户应用及命名空间的列表
            //ClientInterface::Instance()->updateXMLNSList(xmlns_list_,list,sock);
        }else
        {
            strcpy((char*)buf_,"No");
        }
        sock->async_send(asio::buffer(buf_,strlen((const char*)buf_)+1),
                         boost::bind(&TCPServer::handle_write,
                         this,asio::placeholders::error,sock));

    }else if ( CMD_NORMAL == ret )
    {
        onSendData(qstr); //交由XMPP发送
        //sprintf((char*)data_,"Ok");
        //sock->async_send(asio::buffer(data_,strlen((const char*)data_)+1),
        //                 boost::bind(&TCPServer::handle_write,
        //                this,asio::placeholders::error,sock));
    }
}
void TCPServer::sendRawData(QString str)
{
    sprintf((char*)buf_,str.toStdString().c_str());
    QList<socket_pointer>::iterator  sit = socklist_.begin();
    for ( ;sit != socklist_.end(); ++sit)
    {
        (*sit)->async_send(asio::buffer(buf_,strlen((const char*)buf_)+1),
                           boost::bind(&TCPServer::handle_write,
                           this,asio::placeholders::error,*sit));
    }
}


void TCPServer::flushMessages()
{
    //
    QStringList keys = map_sock.keys();
    int count = keys.count();

    for ( int i = 0 ; i < count; ++i)
    {
        socket_pointer sock = map_sock[keys[i]];
        QString content = map_pushlist[keys[i]];
        sprintf((char*)buf_,content.toStdString().c_str());
        sock->async_send(asio::buffer(buf_,strlen((const char*)buf_)+1),
                           boost::bind(&TCPServer::handle_write,
                           this,asio::placeholders::error,sock));
    }


}

void TCPServer::sendXmlns(QString xmlns, QString qstr)
/*
*  将指定命名空间的报文发送给已注册接收该报文的用户
*
*/
{
    XMLNSList::iterator  it = xmlns_list_.begin();
    for ( ; it != xmlns_list_.end(); ++it)
    {
        if ( xmlns == it->xmlns_ )
        {
            //显然，一个socket对应着一个注册用户
            QList<socket_pointer>::iterator  sit = it->sock_list_.begin();
            for ( ;sit != it->sock_list_.end(); ++sit)
            {
                sprintf((char*)buf_,qstr.toStdString().c_str());
                (*sit)->async_send(asio::buffer(buf_,strlen((const char*)buf_)+1),
                                   boost::bind(&TCPServer::handle_write,
                                   this,asio::placeholders::error,*sit));

            }
        }
    }
}
void TCPServer::openio()
{
    io_.run();
}

void TCPServer::setMessagesToPush(QMap<QString, QString> msgs)
{
    map_pushlist = msgs;
}
void TCPServer::pushMessage(QString app, QString msg)
{
    QMap<QString,socket_pointer>::iterator it = map_sock.find("desktop");
    qDebug()<<"Push message";
    if ( it == map_sock.end() )
    {
        qDebug()<<"Can not find desktop sock";
        return;
    }
    socket_pointer sock = (*it);
    static char buf[MAX_MESSAGE_LENGTH] = {0};
    msg = app+"=" + msg;

    strncpy(buf,msg.toLocal8Bit().data()
            ,strlen(msg.toLocal8Bit().data()) + 1);
    qDebug()<<"Sendto Desktop:"<<QString::fromLocal8Bit(buf);
    sock->async_send(asio::buffer(buf,strlen(buf)+1),
                   boost::bind(&TCPServer::handle_write,
                   this,asio::placeholders::error,sock));
}

void TCPServer::pushMessages(QStringList keys)
{
    int i = 0;
    QString key;
    static char buf[MAX_MESSAGE_LENGTH] = {0};

    for ( i = 0 ; i < keys.size(); ++i)
    {
        key = keys[i];

        socket_pointer sock = map_sock[key];
        strncpy( buf,map_pushlist[key].toStdString().c_str()
                 ,map_pushlist[key].toStdString().length() + 1);
        sock->async_send(asio::buffer(buf,strlen(buf)+1),
                       boost::bind(&TCPServer::handle_write,
                       this,asio::placeholders::error,sock));
        map_pushlist.erase( map_pushlist.find(key) );
    }

}

void TCPServer::run()
{
     boost::thread  th(boost::bind(&TCPServer::openio,this));
}
