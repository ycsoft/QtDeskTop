#ifndef MYSOCK_H
#define MYSOCK_H


#include "datatypes.h"

#include <QObject>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <map>
#include <QFile>
#include <QThread>
#include <QMutexLocker>
#include <QMutex>
#include <QHash>
#include <QFile>
#include <QStringList>




#pragma pack(1)

using namespace  boost;
typedef unsigned char uchar;
using namespace std;

class QFileProgress;
class QFileRecv;

class MySock : public QObject
{
    Q_OBJECT
public:
    typedef QHash<QString,QFile*>   HashFile;
    MySock(boost::asio::io_service &io);
    ~MySock();

    typedef  boost::shared_ptr<asio::ip::tcp::socket> sock_pt;
    typedef  boost::asio::ip::tcp::socket  tcpSocket;
    void start(const char* ip, int port);
    void senddata(void *buf, int len);
    void connecthandle(const boost::system::error_code &ec, sock_pt sk);
    void readhandle(const boost::system::error_code &ec,size_t bytes_transfferd);
    void writehandle(const boost::system::error_code &ec);
    void run();
    void stop();
    void    handleData(uchar *data);

    bool    isconnected() const { return connected;}
    void setFile(QFile *f)
    {
        c_file = f;
    }
    QStringList getFileList()
    {
        return h_filelist;
    }

    HashFile    getHashSend() { return hash_send;}
    HashFile    getHashRecv() { return hash_recv;}

    void        setHashSend(QString fn,QFile *f) { hash_send[fn] = f;}
    void        setHashRecv(QString fn,QFile *f) { hash_recv[fn] = f;}
    void        setHashOffline(QString fn,QFile *f) { hash_offline[fn] = f;}
signals:
    //共享文件
    void addShareFile(const char *);
    //继续发送
    void signalSendContinue(QFile *f);
    //接受进度
    void signalprogress(uint transed,uint total);
    //接收完毕
    void sendcomplete(const char* from, const char *to, const char *filename);
    void offline(const char*);
    void finished(const char *from,const char *filename);
    //是否接收文件
    bool fileRequest(const char* from, const char *to, const char *filename);
    //发送文件
    void acceptfileSend(const char *from, const char *to, const char *filename);
    //文件数据
    void receiveFileData(const char *from, const char *to, const char *filename, uint transed, uint total,uchar *data);
public slots:
protected:
    void        continueRecv();
    void        recvHead();
private:
    sock_pt     _sock;
    asio::io_service    &_ios;
    boost::thread       m_thread;

    uchar       *c_buf;
    uchar       *c_tmpbuf;
    uchar       *m_head;

    QFile       *c_file;
    QFile       *c_log;
    QMutex      c_mutex;
    QFileProgress   *m_progress;
    QFileRecv       *m_recv;
    bool        connected;
    HashFile   hash_send;
    HashFile   hash_recv;
    HashFile   hash_offline;
    QStringList     h_filelist;

    bool        pack_ok;

};

#endif // MYSOCK_H
