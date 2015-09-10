#ifndef DATATYPES_H
#define DATATYPES_H
#include <boost/asio.hpp>
#include <QList>
#include <QString>
#pragma pack(1)


#define  JID_LEN    64
#define  DATA_LEN   10240
#define  FILE_NAME_LEN 256
typedef unsigned char uchar;
typedef unsigned short ushort;

typedef unsigned int  uint32;

#define  ONLINE             0       //上线
#define  OFFLINE            4       //用户下线
#define  SEND_REQ           1       //文件发送请求
#define  REJECT_REQ         2       //拒绝接收
#define  TRANS_DATA         3       //在线文件数据
#define  ACCEPT_FILE        5       //同意接收
#define  OFFLINE_FILE       6       //离线文件
#define  SEND_COMPLETE      7       //发送完毕
#define  SEND_CONTINUE      8       //继续发送
#define  OFF_DATA           9       //离线数据
#define  DOWNLOAD_FILE      10      //下载文件
#define  FILE_LIST          11      //文件列表

#define  Packet             2

#define  SOCK_BUF_LEN       (DATA_LEN + 399 + Packet)

#define  CURRENT_VERSION    1.0

#define  Installer_Name           "SafeThrough(1).exe"
#define  Default_IP               "192.168.1.101"



#define  PacketLen(X)       (sizeof(X)-2)

#define LOCAL(X) QString::fromLocal8Bit(X)

namespace datatype {

struct Head
{
    ushort len;
    uchar h1;
    uchar h2;
    uchar h3;
    uchar h4;
    uchar vsn;
    ushort flag;
    Head()
    {
        h1 = 0;
        h2 = 0;
        h3 = 0;
        h4 = 0;
        vsn = 1;
        flag = 0;
    }
};
//上线
struct online
{
    Head head;
    char jid[JID_LEN];
    online()
    {
        head.len = htons( PacketLen(online) );
        head.flag = htons(0);
        memset(jid,0,JID_LEN);
    }
};
//请求发送文件
struct requestSendFile
{
        Head head;
        char fromjid[JID_LEN];
        char jid[JID_LEN];
        char filename[FILE_NAME_LEN];
        requestSendFile()
        {
            head.flag = htons(1);
            head.len = htons( PacketLen(requestSendFile) );
            memset(fromjid,0,JID_LEN);
            memset(jid,0,JID_LEN);
            memset(filename,0,FILE_NAME_LEN);
        }
};
//同意接受
struct acceptTrans
{
        Head head;
        char fromjid[JID_LEN];
        char jid[JID_LEN];
        char filename[FILE_NAME_LEN];
        acceptTrans()
        {
            head.flag = htons(5);

            head.len = htons( PacketLen(acceptTrans) );
            memset(fromjid,0,JID_LEN);
            memset(jid,0,JID_LEN);
            memset(filename,0,FILE_NAME_LEN);
        }
};
//拒绝接收
struct rejectTrans
{
        Head head;
        char fromjid[JID_LEN];
        char jid[JID_LEN];
        char filename[FILE_NAME_LEN];
        rejectTrans()
        {
            head.flag = htons(2);
            head.len = htons( PacketLen(rejectTrans) );
            memset(fromjid,0,JID_LEN);
            memset(jid,0,JID_LEN);
            memset(filename,0,FILE_NAME_LEN);
        }
};
//用户离线
struct useroffline
{
        Head head;
        char jid[JID_LEN];
        useroffline()
        {
            head.flag = htons(4);
            head.len = htons( PacketLen(useroffline) );
            memset(jid,0,JID_LEN);
        }
};
//离线传输
struct offlineTrans
{
        Head head;
        char fromjid[JID_LEN];
        char jid[JID_LEN];
        char filename[FILE_NAME_LEN];
        offlineTrans()
        {
            head.flag = htons(6);
            head.len = htons( PacketLen(offlineTrans) );
            memset(fromjid,0,JID_LEN);
            memset(jid,0,JID_LEN);
            memset(filename,0,FILE_NAME_LEN);
        }
};

//文件数据
struct senddata
{
        Head head;
        char fromjid[JID_LEN];
        char tojid[JID_LEN];
        char filename[FILE_NAME_LEN];
        uint32  total;
        uint32  transfered;
        uchar   data[DATA_LEN];
        senddata()
        {
            //data = new uchar[DATA_LEN];
            head.flag = htons(3);
            head.len = htons( PacketLen(senddata) );
            transfered = 0;
            total = 0;
            memset(data,0,DATA_LEN);
            memset(fromjid,0,JID_LEN);
            memset(tojid,0,JID_LEN);
            memset(filename,0,FILE_NAME_LEN);
        }
        ~senddata()
        {
            //delete [] data;
            //data = NULL;
        }
};
//离线文件数据
struct offlinedata
{
        Head head;
        char fromjid[JID_LEN];
        char tojid[JID_LEN];
        char filename[FILE_NAME_LEN];
        uint32  total;
        uint32  transfered;
        uchar   data[DATA_LEN];
        offlinedata()
        {
            //data = new uchar[DATA_LEN];
            head.flag = htons(9);
            head.len = htons( PacketLen(offlinedata) );
            transfered = 0;
            total = 0;
            memset(data,0,DATA_LEN);
            memset(fromjid,0,JID_LEN);
            memset(tojid,0,JID_LEN);
            memset(filename,0,FILE_NAME_LEN);
        }
        ~offlinedata()
        {
            //delete [] data;
            //data = NULL;
        }
};
//发送完毕
struct sendcomplete
{
        Head head;
        char fromjid[JID_LEN];
        char jid[JID_LEN];
        char filename[FILE_NAME_LEN];
        sendcomplete()
        {
            head.flag = htons(7);
            head.len = htons( PacketLen(sendcomplete) );
            memset(fromjid,0,JID_LEN);
            memset(jid,0,JID_LEN);
            memset(filename,0,FILE_NAME_LEN);
        }
};
//继续发送
struct sendcontinue
{
        Head head;
        char fromjid[JID_LEN];
        char jid[JID_LEN];
        char filename[FILE_NAME_LEN];
        sendcontinue()
        {
            head.flag = htons(8);
            head.len = htons( PacketLen(sendcomplete) );
            memset(fromjid,0,JID_LEN);
            memset(jid,0,JID_LEN);
            memset(filename,0,FILE_NAME_LEN);
        }
};
//获取文件列表
struct getFileList
{
    Head    head;
    char    fromjid[JID_LEN];
    getFileList()
    {
        head.flag = htons(11);
        head.len = htons(PacketLen(getFileList));
        memset(fromjid,0,JID_LEN);
    }
};
//返回文件列表
struct filelist
{
    Head head;
    char value[FILE_NAME_LEN];
    filelist()
    {
        head.flag = htons(11);
        head.len = htons( PacketLen(filelist));
        memset(value,0,FILE_NAME_LEN);
    }
};
//请求下载离线文件
struct downloadFile
{
    Head head;
    char jid[JID_LEN];
    char filename[FILE_NAME_LEN];
    downloadFile()
    {
        head.flag = htons(10);
        head.len  = htons( PacketLen(downloadFile));
        memset(filename,0,FILE_NAME_LEN);
        memset(jid,0,JID_LEN);
    }
};

struct XMLNSData
{
   typedef boost::asio::ip::tcp::socket	tcpsocket;
   typedef boost::shared_ptr<tcpsocket> socket_pointer;
   QString xmlns_;
   QList<socket_pointer>  sock_list_;
};

typedef QList<XMLNSData>  XMLNSList;
}
#endif // DATATYPES_H
