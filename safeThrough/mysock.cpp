#include "mysock.h"


#include <boost/thread.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <QDebug>

#ifndef LOCAL(x)
#define LOCAL(x) QString::fromLocal8Bit(x)
#endif

using namespace datatype;
MySock::MySock(asio::io_service &io):_ios(io),_sock(new asio::ip::tcp::socket(io))
,pack_ok(false){
    connected = false;
    c_log = new QFile("log.txt");
    c_log->open(QIODevice::Append);
    c_buf = new uchar[SOCK_BUF_LEN];
    c_tmpbuf = new uchar[SOCK_BUF_LEN];
    m_head   = new uchar[sizeof(Head)];

    /*bool check = false;

    check = QObject::connect(this,SIGNAL(signalprogress(uint,uint)),m_recv,
                             SLOT(slotProgress(uint,uint)),Qt::BlockingQueuedConnection);
    Q_ASSERT(check);
    */
}
MySock::~MySock()
{
    c_log->close();
    if (c_buf){
    delete [] c_buf;
    c_buf = NULL;
    }
    if (c_tmpbuf){
    delete [] c_tmpbuf;
    c_tmpbuf = NULL;
    }
}
/**
 * @brief MySock::stop
 * 关闭SOCKET，终止数据接收线程
 */
void MySock::stop()
{
    _sock->close();
    connected = false;
    //m_thread.timed_join(boost::posix_time::milliseconds(100));
}
/**
 * @brief MySock::start
 * @param ip   服务器IP地址
 * @param port 服务器端口号
 * 设置SOCKET属性：取消nagle，设置发送、接收缓冲区,
 * 然后建立对指定服务器的连接
 */
void MySock::start(const char* ip, int port)
{
    boost::asio::ip::tcp::endpoint  ep(asio::ip::address::from_string(ip),port);
    boost::system::error_code ec;
    boost::asio::ip::tcp::no_delay  option(true);
    boost::asio::ip::tcp::socket::send_buffer_size sndbuf(SOCK_BUF_LEN);
    boost::asio::ip::tcp::socket::receive_buffer_size recvbuf(2*SOCK_BUF_LEN);

    //_sock = sock_pt(new asio::ip::tcp::socket(_ios));

    _sock->set_option(recvbuf,ec);
    _sock->set_option(option,ec);
    _sock->set_option(sndbuf,ec);
    _sock->connect(ep,ec);
    if (ec)
    {
        connected = false;
        return;
    }
    //_sock->async_connect(ep,boost::bind(&MySock::connecthandle,this,asio::placeholders::error,_sock));
    connected = true;
    memset(c_buf,0,SOCK_BUF_LEN);
    memset(c_tmpbuf,0,SOCK_BUF_LEN);
    memset(m_head,0,sizeof(Head));
    //_sock->async_receive(asio::buffer(c_buf,SOCK_BUF_LEN),boost::bind(&MySock::readhandle,this,asio::placeholders::error,c_buf));
    //continueRecv();
    m_thread =  boost::thread(&MySock::run,this);
}
/**
 * @brief MySock::run
 *
 *  数据接收线程
 *  先接收数据包头，根据包头指定的数据包长度接收余下数据
 *
 */
void MySock::run()
{
    while ( connected )
    {
        qDebug()<<"Recving.....";
        recvHead();
    }
    qDebug()<<"Thread Exit";
    //_ios.run();
}

void MySock::connecthandle(const system::error_code &ec, sock_pt sk)
{
    connected = true;
    memset(c_buf,0,SOCK_BUF_LEN);
    memset(c_tmpbuf,0,SOCK_BUF_LEN);
    //_sock->async_receive(asio::buffer(c_buf,SOCK_BUF_LEN),boost::bind(&MySock::readhandle,this,asio::placeholders::error,c_buf));
    //continueRecv();
}
void MySock::handleData(uchar *data)
{
    bool b = true;
    memset(c_tmpbuf,0,SOCK_BUF_LEN);
    memcpy_s(c_tmpbuf,SOCK_BUF_LEN,data,SOCK_BUF_LEN);
    Head *head = reinterpret_cast<Head*>(c_tmpbuf);
    //qDebug()<<"Recv new Data: "<<ntohs(head->flag)<<" SOCK_BUF:"<<SOCK_BUF_LEN<<" bytes_transfferd:"<<bytes_transfferd;
    int flag = 0;
    flag = ntohs(head->flag);
    switch (flag) {
    case ONLINE:
        memset(c_buf,0,SOCK_BUF_LEN);
        break;
    case OFFLINE:
    {
        useroffline *off = reinterpret_cast<useroffline*>(c_tmpbuf);
        char jid[JID_LEN] = {0};
        memcpy_s(jid,JID_LEN,off->jid,JID_LEN);
        emit offline(jid);

        break;
    }
    case SEND_REQ:
    {
        requestSendFile *rsend = reinterpret_cast<requestSendFile*>(c_tmpbuf);
        char cfrom[JID_LEN] = {0}, cto[JID_LEN] = {0},cfile[FILE_NAME_LEN] = {0};
        memcpy_s(cfrom,JID_LEN,rsend->fromjid,JID_LEN);
        memcpy_s(cto,JID_LEN,rsend->jid,JID_LEN);
        memcpy_s(cfile,FILE_NAME_LEN,rsend->filename,FILE_NAME_LEN);
        if(fileRequest(cfrom,cto,cfile))
            qDebug()<<"Accept File Transfer Request";

        break;
    }
    case REJECT_REQ:
    {
        rejectTrans  *reject = reinterpret_cast<rejectTrans*>(c_tmpbuf);

        break;
    }
    case ACCEPT_FILE:
    {
        qDebug()<<"Accept Our File";
        acceptTrans *accpt = reinterpret_cast<acceptTrans*>(c_tmpbuf);
        char path[FILE_NAME_LEN] = {0};
        char from[JID_LEN] = {0};
        char to[JID_LEN] = {0};
        QString qs = QString::fromLocal8Bit(accpt->filename,FILE_NAME_LEN);
        memcpy_s(path,FILE_NAME_LEN,qs.toLocal8Bit().data(),FILE_NAME_LEN);

        memcpy_s(from,JID_LEN,accpt->fromjid,JID_LEN);
        memcpy_s(to,JID_LEN,accpt->jid,JID_LEN);
        emit acceptfileSend(from,to,path);

        break;
    }
        //请求下载离线文件
    case DOWNLOAD_FILE:
    {
        datatype::downloadFile *down = reinterpret_cast<datatype::downloadFile*>(c_tmpbuf);
        char file[FILE_NAME_LEN] = {0};
        memcpy_s(file,FILE_NAME_LEN,down->filename,FILE_NAME_LEN);
        QString fn = QString::fromLocal8Bit(file);

        break;
    }
    case OFF_DATA:
    {
        int total = 0;
        datatype::offlinedata   *offdata = reinterpret_cast<datatype::offlinedata*>(c_tmpbuf);
        char file[FILE_NAME_LEN] = {0};
        memcpy_s(file,FILE_NAME_LEN,offdata->filename,FILE_NAME_LEN);
        QString fn = QString::fromLocal8Bit(file);
        static QHash<QString,uint>  donehash;
        if ( hash_offline.contains(fn))
        {
            int len = ntohl(offdata->transfered);
            donehash[fn] += len;
            total = ntohl(offdata->total);
            qDebug()<<"off line data done:"<<donehash[fn]<<" total:"<<total;
            emit signalprogress(donehash[fn],total);
            QFile *f = hash_offline[fn];
            f->write((char*)offdata->data,len);
            if ( donehash[fn] >= total)
            {
                donehash[fn] = 0;
                f->close();
                emit finished(offdata->fromjid,offdata->filename);
            }
            //datatype::sendcontinue  sc;
            //senddata(&sc,sizeof(sc));

        }else{
            qDebug()<<"cannot find file in hash";
        }
        b = false;
        break;
    }
    case TRANS_DATA:
    {
        qDebug()<<"Transmission data";
        static int tc = 1;

        datatype::senddata *sd = reinterpret_cast<datatype::senddata*>(c_tmpbuf);
        char from[JID_LEN] = {0};
        char to[JID_LEN]    = {0};
        char filename[FILE_NAME_LEN] = {0};

        uint  total = ntohl(sd->total);
        uint  transed = ntohl(sd->transfered);
        //uint  value = MyLock::Instance()->getTransed();
        //value = value + transed;
        //MyLock::Instance()->setTransed( value);
        uchar   udata[DATA_LEN] = {0};
        memset(udata,0,DATA_LEN);
        //memset(c_tmpbuf,0,DATA_LEN);
        memcpy_s(from,JID_LEN,sd->fromjid,JID_LEN);
        memcpy_s(to,JID_LEN,sd->tojid,JID_LEN);
        memcpy_s(udata,DATA_LEN,sd->data,DATA_LEN);
        memcpy_s(filename,FILE_NAME_LEN,sd->filename,FILE_NAME_LEN);
        if (total <= 0 )
        {

            return;
        }

        break;
    }
    case SEND_COMPLETE:
    {
        datatype::sendcomplete *scmp = reinterpret_cast<datatype::sendcomplete*>(c_tmpbuf);
        char from[JID_LEN] = {0};
        char to[JID_LEN]    = {0};
        char filename[FILE_NAME_LEN] = {0};
        memcpy_s(from,JID_LEN,scmp->fromjid,JID_LEN);
        memcpy_s(to,JID_LEN,scmp->jid,JID_LEN);
        memcpy_s(filename,FILE_NAME_LEN,scmp->filename,FILE_NAME_LEN);
        emit  sendcomplete(from,to,filename);
        //MyLock::Instance()->setTransed(0);

        break;
    }
    case SEND_CONTINUE:
    {

        qDebug()<<"send Continue!";
        static int value = DATA_LEN;
        sendcontinue *scont = reinterpret_cast<sendcontinue*>(c_tmpbuf);
        static      int count = 1;
        char        cc[10] = {0};
        char       cfrom[JID_LEN] = {0};
        char       cto[JID_LEN]     = {0};
        char       cfile[FILE_NAME_LEN] = {0};
        datatype::senddata    sd;
        uint     size = 0;
        uchar    udata[DATA_LEN];
        //uchar      udata[DATA_LEN];
        uint32     len = 0;
        uint32     sum = 0;
        //uint       value = MyLock::Instance()->getTransed();

        memcpy_s(cfrom,JID_LEN,scont->fromjid,JID_LEN);
        memcpy_s(cto,JID_LEN,scont->jid,JID_LEN);
        memcpy_s(cfile,FILE_NAME_LEN,scont->filename,FILE_NAME_LEN);
        QString fn = QString::fromLocal8Bit(cfile);
        QFile   *file = NULL;
        if ( hash_send.contains(fn))
            file = hash_send[fn];
        else
        {

            break;
        }
        c_file = file;

        size = file->size();
        sprintf(cc,"%d",count++);

        c_log->write("recv continue.........");
        c_log->write(cc);
        c_log->write("\n");

        memset(udata,0,DATA_LEN);

        c_log->write(cfrom);
        c_log->write(":");
        c_log->write(cto);
        c_log->write(":");
        c_log->write(cfile);
        c_log->write("\n");

        if (value >= size)
        {
            c_file->close();
            datatype::sendcomplete scp;
            memcpy_s(scp.fromjid,JID_LEN,cfrom,JID_LEN);
            memcpy_s(scp.jid,JID_LEN,cto,JID_LEN);
            memcpy_s(scp.filename,FILE_NAME_LEN,cfile,FILE_NAME_LEN);
            Sleep(800);
            senddata(&scp,sizeof(scp));

            break;
        }
        len = c_file->read(reinterpret_cast<char*>(udata),DATA_LEN);
        sum = len;
        value += sum;
        memcpy_s(sd.fromjid,JID_LEN,cfrom,JID_LEN);
        memcpy_s(sd.tojid,JID_LEN,cto,JID_LEN);
        memcpy_s(sd.filename,FILE_NAME_LEN,cfile,FILE_NAME_LEN);
        memcpy_s(sd.data,DATA_LEN,udata,DATA_LEN);

        sd.total = htonl(size);
        sd.transfered = htonl(sum);
        c_log->write("begin send, to:");
        c_log->write(sd.tojid);
        c_log->write("\n");
        senddata(&sd,sizeof(sd));
        c_log->write("send over\n");
        //emit progressMax(size);
       //emit progress(value);
        signalprogress(value,size);
        //MyLock::Instance()->setTransed(value);
        if (value >= size || len == 0)
        {
            c_file->close();
            datatype::sendcomplete scp;
            memcpy_s(scp.fromjid,JID_LEN,cfrom,JID_LEN);
            memcpy_s(scp.jid,JID_LEN,cto,JID_LEN);
            memcpy_s(scp.filename,FILE_NAME_LEN,cfile,FILE_NAME_LEN);
            Sleep(800);
            senddata(&scp,sizeof(scp));

        }

        break;
    }
    case OFFLINE_FILE:
    {
        offlineTrans *ot = reinterpret_cast<offlineTrans*>(c_tmpbuf);

        break;
    }
    case FILE_LIST:
    {
        datatype::filelist    *filelist = reinterpret_cast<datatype::filelist *>(c_tmpbuf);
        char        cfile[FILE_NAME_LEN] = {0};
        memcpy_s(cfile,FILE_NAME_LEN,filelist->value,FILE_NAME_LEN);
        h_filelist.append(QString::fromLocal8Bit(cfile));
        c_log->write(cfile);
        c_log->write("\r\n");
        c_log->flush();
        emit addShareFile(cfile);

        break;
    }
    default:
        break;
    }
}

void MySock::recvHead()
{
    datatype::Head *head;
    uchar      buf[SOCK_BUF_LEN] = {0};
    boost::system::error_code ec;

    qDebug()<<"Ready to Read Head";
    size_t sz = _sock->receive(boost::asio::buffer(m_head,sizeof(Head)),0,ec);
    qDebug()<<"RecvHead: "<<sz;
    while ( sz < sizeof(Head))
    {
        if (!isconnected())
            return;
       sz += _sock->receive(boost::asio::buffer(m_head+sz,sizeof(Head)-sz),0,ec);
    }
    memcpy_s(buf,SOCK_BUF_LEN,m_head,sizeof(Head));
    head = reinterpret_cast<Head*>(m_head);
    //获取实际数据包的长度
    int len = ntohs(head->len);
    /*if (len > SOCK_BUF_LEN-Packet)
        len = SOCK_BUF_LEN - Packet;
    */
    len = len - (sizeof(Head)) + Packet;
    memset(m_head,0,sizeof(Head));
    if ( !isconnected())
        return;
    qDebug()<<"Ready to recv packet body: ";
    sz = _sock->receive(boost::asio::buffer(c_buf,len),0,ec);
    qDebug()<<"Recv packet body successful";
    while ( sz < len)
    {
        if (!isconnected())
            return;
        sz += _sock->receive(boost::asio::buffer(c_buf+sz,len-sz));
    }
    qDebug()<<LOCAL("实际包长:")<<len;
    memcpy_s(buf+sizeof(Head),len,c_buf,len);
    //TODO:处理接受到的数据
    handleData(buf);
    memset(c_buf,0,SOCK_BUF_LEN);
}

void MySock::readhandle(const system::error_code &ec, size_t bytes_transfferd)
{
    bool b = true;
    if (ec)
    {
        continueRecv();
        return;
    }
    memset(c_tmpbuf,0,SOCK_BUF_LEN);
    memcpy_s(c_tmpbuf,SOCK_BUF_LEN,c_buf,SOCK_BUF_LEN);
    Head *head = reinterpret_cast<Head*>(c_tmpbuf);
    qDebug()<<"Recv new Data: "<<ntohs(head->flag)<<" SOCK_BUF:"<<SOCK_BUF_LEN<<" bytes_transfferd:"<<bytes_transfferd;
    int flag = 0;
    flag = ntohs(head->flag);
    switch (flag) {
    case ONLINE:
        memset(c_buf,0,SOCK_BUF_LEN);
        break;
    case OFFLINE:
    {
        useroffline *off = reinterpret_cast<useroffline*>(c_tmpbuf);
        char jid[JID_LEN] = {0};
        memcpy_s(jid,JID_LEN,off->jid,JID_LEN);
        emit offline(jid);

        break;
    }
    case SEND_REQ:
    {
        requestSendFile *rsend = reinterpret_cast<requestSendFile*>(c_tmpbuf);
        char cfrom[JID_LEN] = {0}, cto[JID_LEN] = {0},cfile[FILE_NAME_LEN] = {0};
        memcpy_s(cfrom,JID_LEN,rsend->fromjid,JID_LEN);
        memcpy_s(cto,JID_LEN,rsend->jid,JID_LEN);
        memcpy_s(cfile,FILE_NAME_LEN,rsend->filename,FILE_NAME_LEN);
        if(fileRequest(cfrom,cto,cfile))
            qDebug()<<"Accept File Transfer Request";

        break;
    }
    case REJECT_REQ:
    {
        rejectTrans  *reject = reinterpret_cast<rejectTrans*>(c_tmpbuf);

        break;
    }
    case ACCEPT_FILE:
    {
        qDebug()<<"Accept Our File";
        acceptTrans *accpt = reinterpret_cast<acceptTrans*>(c_tmpbuf);
        char path[FILE_NAME_LEN] = {0};
        char from[JID_LEN] = {0};
        char to[JID_LEN] = {0};
        QString qs = QString::fromLocal8Bit(accpt->filename,FILE_NAME_LEN);
        memcpy_s(path,FILE_NAME_LEN,qs.toLocal8Bit().data(),FILE_NAME_LEN);

        memcpy_s(from,JID_LEN,accpt->fromjid,JID_LEN);
        memcpy_s(to,JID_LEN,accpt->jid,JID_LEN);
        emit acceptfileSend(from,to,path);

        break;
    }
        //请求下载离线文件
    case DOWNLOAD_FILE:
    {
        datatype::downloadFile *down = reinterpret_cast<datatype::downloadFile*>(c_tmpbuf);
        char file[FILE_NAME_LEN] = {0};
        memcpy_s(file,FILE_NAME_LEN,down->filename,FILE_NAME_LEN);
        QString fn = QString::fromLocal8Bit(file);

        break;
    }
    case OFF_DATA:
    {
        int total = 0;
        datatype::offlinedata   *offdata = reinterpret_cast<datatype::offlinedata*>(c_tmpbuf);
        char file[FILE_NAME_LEN] = {0};
        memcpy_s(file,FILE_NAME_LEN,offdata->filename,FILE_NAME_LEN);
        QString fn = QString::fromLocal8Bit(file);
        static QHash<QString,uint>  donehash;
        if ( hash_offline.contains(fn))
        {
            int len = ntohl(offdata->transfered);
            donehash[fn] += len;
            total = ntohl(offdata->total);
            qDebug()<<"off line data done:"<<donehash[fn]<<" total:"<<total;
            emit signalprogress(donehash[fn],total);
            QFile *f = hash_offline[fn];
            f->write((char*)offdata->data,len);
            if ( donehash[fn] >= total)
            {
                donehash[fn] = 0;
                f->close();
                emit finished(offdata->fromjid,offdata->filename);
            }
            datatype::sendcontinue  sc;
            senddata(&sc,sizeof(sc));

        }else{
            qDebug()<<"cannot find file in hash";
        }
        b = false;
        break;
    }
    case TRANS_DATA:
    {
        qDebug()<<"Transmission data";
        static int tc = 1;

        datatype::senddata *sd = reinterpret_cast<datatype::senddata*>(c_tmpbuf);
        char from[JID_LEN] = {0};
        char to[JID_LEN]    = {0};
        char filename[FILE_NAME_LEN] = {0};

        uint  total = ntohl(sd->total);
        uint  transed = ntohl(sd->transfered);
        //uint  value = MyLock::Instance()->getTransed();
        //value = value + transed;
        //MyLock::Instance()->setTransed( value);
        uchar   udata[DATA_LEN] = {0};
        memset(udata,0,DATA_LEN);
        //memset(c_tmpbuf,0,DATA_LEN);
        memcpy_s(from,JID_LEN,sd->fromjid,JID_LEN);
        memcpy_s(to,JID_LEN,sd->tojid,JID_LEN);
        memcpy_s(udata,DATA_LEN,sd->data,DATA_LEN);
        memcpy_s(filename,FILE_NAME_LEN,sd->filename,FILE_NAME_LEN);
        if (total <= 0 )
        {

            return;
        }

        break;
    }
    case SEND_COMPLETE:
    {
        datatype::sendcomplete *scmp = reinterpret_cast<datatype::sendcomplete*>(c_tmpbuf);
        char from[JID_LEN] = {0};
        char to[JID_LEN]    = {0};
        char filename[FILE_NAME_LEN] = {0};
        memcpy_s(from,JID_LEN,scmp->fromjid,JID_LEN);
        memcpy_s(to,JID_LEN,scmp->jid,JID_LEN);
        memcpy_s(filename,FILE_NAME_LEN,scmp->filename,FILE_NAME_LEN);
        emit  sendcomplete(from,to,filename);
        //MyLock::Instance()->setTransed(0);

        break;
    }
    case SEND_CONTINUE:
    {

        qDebug()<<"send Continue!";
        static int value = DATA_LEN;
        sendcontinue *scont = reinterpret_cast<sendcontinue*>(c_tmpbuf);
        static      int count = 1;
        char        cc[10] = {0};
        char       cfrom[JID_LEN] = {0};
        char       cto[JID_LEN]     = {0};
        char       cfile[FILE_NAME_LEN] = {0};
        datatype::senddata    sd;
        uint     size = 0;
        uchar    udata[DATA_LEN];
        //uchar      udata[DATA_LEN];
        uint32     len = 0;
        uint32     sum = 0;
        //uint       value = MyLock::Instance()->getTransed();

        memcpy_s(cfrom,JID_LEN,scont->fromjid,JID_LEN);
        memcpy_s(cto,JID_LEN,scont->jid,JID_LEN);
        memcpy_s(cfile,FILE_NAME_LEN,scont->filename,FILE_NAME_LEN);
        QString fn = QString::fromLocal8Bit(cfile);
        QFile   *file = NULL;
        if ( hash_send.contains(fn))
            file = hash_send[fn];
        else
        {

            break;
        }
        c_file = file;

        size = file->size();
        sprintf(cc,"%d",count++);

        c_log->write("recv continue.........");
        c_log->write(cc);
        c_log->write("\n");

        memset(udata,0,DATA_LEN);

        c_log->write(cfrom);
        c_log->write(":");
        c_log->write(cto);
        c_log->write(":");
        c_log->write(cfile);
        c_log->write("\n");

        if (value >= size)
        {
            c_file->close();
            datatype::sendcomplete scp;
            memcpy_s(scp.fromjid,JID_LEN,cfrom,JID_LEN);
            memcpy_s(scp.jid,JID_LEN,cto,JID_LEN);
            memcpy_s(scp.filename,FILE_NAME_LEN,cfile,FILE_NAME_LEN);
            Sleep(800);
            senddata(&scp,sizeof(scp));

            break;
        }
        len = c_file->read(reinterpret_cast<char*>(udata),DATA_LEN);
        sum = len;
        value += sum;
        memcpy_s(sd.fromjid,JID_LEN,cfrom,JID_LEN);
        memcpy_s(sd.tojid,JID_LEN,cto,JID_LEN);
        memcpy_s(sd.filename,FILE_NAME_LEN,cfile,FILE_NAME_LEN);
        memcpy_s(sd.data,DATA_LEN,udata,DATA_LEN);

        sd.total = htonl(size);
        sd.transfered = htonl(sum);
        c_log->write("begin send, to:");
        c_log->write(sd.tojid);
        c_log->write("\n");
        senddata(&sd,sizeof(sd));
        c_log->write("send over\n");
        //emit progressMax(size);
       //emit progress(value);
        signalprogress(value,size);
        //MyLock::Instance()->setTransed(value);
        if (value >= size || len == 0)
        {
            c_file->close();
            datatype::sendcomplete scp;
            memcpy_s(scp.fromjid,JID_LEN,cfrom,JID_LEN);
            memcpy_s(scp.jid,JID_LEN,cto,JID_LEN);
            memcpy_s(scp.filename,FILE_NAME_LEN,cfile,FILE_NAME_LEN);
            Sleep(800);
            senddata(&scp,sizeof(scp));

        }

        break;
    }
    case OFFLINE_FILE:
    {
        offlineTrans *ot = reinterpret_cast<offlineTrans*>(c_tmpbuf);

        break;
    }
    case FILE_LIST:
    {
        datatype::filelist    *filelist = reinterpret_cast<datatype::filelist *>(c_tmpbuf);
        char        cfile[FILE_NAME_LEN] = {0};
        memcpy_s(cfile,FILE_NAME_LEN,filelist->value,FILE_NAME_LEN);
        h_filelist.append(QString::fromLocal8Bit(cfile));
        c_log->write(cfile);
        c_log->write("\r\n");
        c_log->flush();
        emit addShareFile(cfile);

        break;
    }
    default:
        break;
    }
    //c_mutex.unlock();
    //if (b)
    continueRecv();
}
void MySock::continueRecv()
{
    memset(c_buf,0,SOCK_BUF_LEN);
    memset(c_tmpbuf,0,SOCK_BUF_LEN);
    _sock->async_receive(asio::buffer(c_buf,SOCK_BUF_LEN),
                         boost::bind(&MySock::readhandle,this,
                         asio::placeholders::error,
                         boost::asio::placeholders::bytes_transferred
                         ));
}

void MySock::writehandle(const system::error_code &ec)
{

}

void MySock::senddata(void *buf, int len)
{
    boost::system::error_code ec;
    if ( !connected)
        return;
    std::size_t transed = boost::asio::write(*(_sock.get()),boost::asio::buffer(buf,len),boost::asio::transfer_all());
}
