#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

#include <QList>
#include <QString>


#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/thread.hpp>

#include <iostream>
#include <Windows.h>
#include <QMap>

#include "CommandParse.hpp"
#include "datatypes.h"
#include "maindialog.h"


#define     BUFLEN  512
#define     MAX_MEM (1024 * 1024) // 1 Mbits


using namespace std;
using namespace boost;
using namespace datatype;

class TCPServer : public QWidget
{
    Q_OBJECT
    //friend class MainWindow;
    //friend class PacketConsle;
public:
    //type declare
    typedef asio::ip::tcp::socket	tcpsocket;
    typedef boost::shared_ptr<tcpsocket> socket_pointer;
    typedef unsigned char byte;
    typedef unsigned short	uint16;

    TCPServer(asio::io_service &ios,int port,QWidget *parent);
    ~TCPServer();
    void start();
    XMLNSList  getXmlnsList();
    void handle_accept(const boost::system::error_code &ec,socket_pointer sock);
    void handle_write(const boost::system::error_code &ec,socket_pointer sock);
    void handle_read(const boost::system::error_code &ec, socket_pointer sock);
    void sendXmlns(QString xmlns,QString qstr);
    void run();
    void openio();

    void setMessagesToPush(QMap<QString,QString> msgs);

    void pushMessage(QString app,QString msg);
    void pushMessages(QStringList keys);
    //要推送的消息
    QMap<QString, QString>  map_pushlist;
signals:
    void onInit(QString str);
    void onNewConnect(QString str);
    bool onConfirm(QList<QString>);
    bool onConfirm(QString);

    void onRecvData(QString);
    void onSendData(QString);
    void onSendRawData(QString);
public slots:
    void sendRawData(QString str);
    void flushMessages();
private:
    asio::io_service&		io_;
    asio::ip::tcp::acceptor	acceptor_;
    byte                    *buf_;
    socket_pointer			sock_;
    //APP -- Sock
    QMap<QString,socket_pointer>   map_sock;

    QList<socket_pointer>   socklist_;
    XMLNSList               xmlns_list_;
    //PacketConsle            *consle_;
};

#endif // TCPSERVER_H
