#ifndef COMMANDPARSE_H
#define COMMANDPARSE_H

#include "session.h"
#include "maindialog.h"
#include "qfloaticon.h"
#include "qutil.h"
#include "caoper.h"

#include <QString>
#include <QList>
#include <QtXml>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QXmppUtils.h>
#include <QTextCodec>
#include <Windows.h>
#include <QMessageBox>


#define  TAGNAME    "CZXP"

#define  CMD_NORMAL 0
#define  CMD_START  1
#define  CMD_ERROR  -1
#define  CMD_LOGIN  2
#define  CMD_PING   3

#define  LOCAL(x) QString::fromLocal8Bit(x)

using namespace std;


class CommandParse
{
public:

    /**
     * @brief parseRandCodeIq
     * @param cmd
     * @param identity
     * @return
     *
     * 解析随机码验证IQ，并返回认证结果
     */
    static bool parseRandCodeIq(const QString cmd,QString &result, int &ret,QString &result2)
    {
        QDomDocument  dom;
        QDomElement   elem;
        QString       tojid,xmlns,authcode,id;
        QString       data;
        ret = -1;

        if ( !dom.setContent(cmd )){
            ret = 2;
            return false;
        }
        //不是符合要求的IQ报文，直接丢弃
        elem = dom.firstChildElement("iq");
        ret = 3;
        if (elem.isNull())
            return false;
        tojid = elem.attribute("from");
        id = elem.attribute("id");
        QString myjid = elem.attribute("to");
        //Session::Instance()->setWholeJid(myjid);
        //Session::Instance()->setjid(QString::fromStdString(JID(myjid.toStdString()).toBare().toString()));
        Session::Instance()->setJID(myjid);
        /*
         *将JID中的用户名提取出来，返回给认证端
         */
        myjid = QXmppUtils::jidToUser(myjid);
        ret = 4;
        if (elem.isNull()) return false;
        ret = 5;
        elem = elem.firstChildElement("CZXP");
        if (elem.isNull()) return false;
        ret = 6;
        xmlns = elem.attribute("xmlns");
        elem = elem.firstChildElement("userAuth");
        if(elem.isNull()) return false;
        ret = 7;
        authcode = elem.lastChild().nodeValue();
        QString realCode = Session::Instance()->getCode("app");
        ret = 0;

        data  = QString("<iq to=\"") + tojid + QString("\" ");
        data += QString(" id=\"")+id + QString("\" type=\"result\">");
        data += QString("<CZXP xmlns=\"") + xmlns + QString("\">");
        data += QString("<userAuth>") + myjid + QString("</userAuth>");
        data += QString("</CZXP>");
        data += QString("</iq>");
        result2 = data;

        if(realCode.compare(authcode) != 0)
        {
            data  = QString("<iq to=\"") + tojid + QString("\" ");
            data += QString(" id=\"")+id + QString("\" type=\"result\">");
            data += QString("<CZXP xmlns=\"") + xmlns + QString("\">");
            data += QString("<userAuth>") + QString("error</userAuth>");
            data += QString("</CZXP>");
            data += QString("</iq>");
            result  = data;
            return false;
        }
        data  = QString("<iq to=\"") + tojid + QString("\" ");
        data += QString(" id=\"")+id + QString("\" type=\"result\">");
        data += QString("<CZXP xmlns=\"") + xmlns + QString("\">");
        data += QString("<userAuth>") + myjid + QString("</userAuth>");
        data += QString("</CZXP>");
        data += QString("</iq>");
        result = data;
        return true;
    }
    /**
     * @brief parseVerifyIq
     * @param cmd
     * @param code
     * @param tojid
     * @return
     *
     * 请求验证的IQ
     *
     */

    static bool  parseVerifyIq(const QString cmd,QString &code, QString &tojid)
    {
        QDomDocument  dom;
        QDomElement   elem;
        //QString scmd = QString("<iq from =\"\",to=\"123\" type=\"result\"><xmlns=\"123\"/><code>xuojfoamdfoaysdYQOEWJN232</code></iq>");
        if ( !dom.setContent(cmd))
        {
            return false;
        }
        elem = dom.firstChildElement(QString("iq"));
        tojid = elem.attribute(QString("from"),QString(""));
        if (elem.isNull())
            return false;
        elem = elem.firstChildElement(QString("code"));
        if (elem.isNull())
            return false;
        code = elem.lastChild().nodeValue();
        return true;
    }

    /**
     * @brief parseCmd
     * @param cmd
     * @param ns
     * @return
     *
     * 解析客户端发送的数据流
     * 解析用户发送的命令,如果是报文,直接转发,返回值为0,否则返回1, ns 中存储命名空间列表
     *开始报文的格式为
     <start>
        <namespace/>
        <namespace/>
        <namespace/>
        <appname/>
        ..
     </start>
     */
    static int     parseCmd(const QString cmd, QList<QString> &ns)
{
    int pos = 0;

    pos = cmd.indexOf(QString("<CZXP"));

    if ( pos < 0)
        return CMD_ERROR;
    pos = cmd.indexOf(QString("iq"));
    if ( pos >= 0) return CMD_NORMAL;
    pos = cmd.indexOf(QString("message"));
    if (pos >= 0) return CMD_NORMAL;
    QDomDocument  dom;
    QDomElement   root;
    //QDomNode      root;
    QDomNodeList  nslist;

    if( !dom.setContent(cmd.toUtf8()))
        return CMD_ERROR;
    //如果没有start节点则认为是正常的报文
    root = dom.firstChild().toElement();
    if ( root.isNull())
        return CMD_NORMAL;
    nslist = root.elementsByTagName(QString("namespace"));
    int sz = nslist.size();
    if ( sz  == 0 )
        return CMD_NORMAL;
    ns.clear();
    for ( pos = 0; pos < sz; ++pos)
    {
        QDomNode    node = nslist.item(pos);
        QString     value = node.lastChild().nodeValue();
        ns.push_back(value);
    }
    return CMD_START;
}
    //////////////////////////////////////////////////////
    /// \brief trimString
    /// \param str
    /// \return
    ///
    /**
    * @brief trimString
    * @param str
    * @return
    */
   static  QString trimString(QString &str)
    {
       char sp[128];
       str = str.trimmed();
       sprintf(sp,str.toStdString().c_str());
       char *h = sp;
       while (*h != '\0')
       {
           if (*h == '\r' || *h == '\n')
               *h = '\0';
           h++;
       }
       str = QString::fromAscii(sp);
       return str;
    }
   /**
     * @brief test
     */
    static void test()
    {
        QFile file("test.txt");
        file.open(QIODevice::ReadOnly);
        QString str = file.readAll(),iq;
        parseVerifyIq(str,str,iq);
    }
    /**
     * @brief createID
     * @return
     */
    static QString createID()
    {
        char seed[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
                      'o','p','q','r','s','t','u','v','w','x','y','z','1','2','3',
                      '4','5','6','7','8','9'};
        int  sz = sizeof(seed);
        int   i = 0;
        QString ret;
        for ( i = 0 ;i < 5; ++i)
        {
            ret.append(seed[rand()%sz]);
        }
        return ret;
    }

    /**
     * @brief createSearchIQ
     * @param search
     * @param srv
     * @return
     */
    static QString createSearchIQ(QString search,QString srv)
    {
      QDomDocument  dom;
      QDomElement   elem;
      int           i = 0;
      id_           =  createID();
      elem = dom.createElement("iq");
      elem.setAttribute("type","set");
      elem.setAttribute("to",srv);
      elem.setAttribute("id",id_);

      QDomElement   query = dom.createElement("query");
      query.setAttribute("xmlns","jabber:iq:search");
      elem.appendChild(query);

      QDomElement   x  = dom.createElement("x");
      x.setAttribute("xmlns","jabber:x:data");
      x.setAttribute("type","submit");
      query.appendChild(x);

      QDomElement   field1  = dom.createElement("field");
      field1.setAttribute("type","hidden");
      field1.setAttribute("var","FORM_TYPE");
      QDomElement   value = dom.createElement("value");
      QDomText      dt = dom.createTextNode("jabber:iq:search");
      value.appendChild(dt);
      field1.appendChild(value);
      x.appendChild(field1);

      QDomElement   field[3];
      QStringList   varlist;
      varlist.append("Username");
      varlist.append("Name");
      varlist.append("Email");
      for ( i = 0 ; i < 3; ++i)
      {
          field[i]= dom.createElement("field");
          field[i].setAttribute("type","boolean");
          field[i].setAttribute("var",varlist[i]);
          QDomElement value = dom.createElement("value");
          QDomText    t = dom.createTextNode("1");
          value.appendChild(t);
          field[i].appendChild(value);
          x.appendChild(field[i]);
      }
      QDomElement  fields = dom.createElement("field");
      fields.setAttribute("type","text-single");
      fields.setAttribute("var","search");
      QDomElement  values = dom.createElement("value");
      QDomText      txt = dom.createTextNode(search);
      values.appendChild(txt);
      fields.appendChild(values);
      x.appendChild(fields);
      dom.appendChild(elem);
      QString xmls = dom.toString();
#if 0
      QFile   file("D:\\iq.txt");
      file.open(QIODevice::WriteOnly);
      file.write(xmls.toAscii());
      file.close();
#endif
      return xmls;
    }
    static bool cmpID(QString id)
    {
        return id.compare(id_);
    }
    ///
    /// \brief id_
    ///
    ///
    ///
    static int parsegetAuth(QString str,QString &ret)
    {
        int          iret = 0;
        QDomDocument dom;

        ret = "";
        if ( !dom.setContent(str))
            return CMD_ERROR;
        QDomElement  elem = dom.documentElement();
        if (elem.isNull())
            return CMD_ERROR;

        QString type = elem.attribute("type","");
        QString app  = elem.attribute("app","");
        qDebug()<<"app="<<app;
        if ( !app.isEmpty() )
            Session::Instance()->setAppName(app);
        if(type == "getcode")
        {
            QString code = CAOper::getCode();
            Session::Instance()->setDCode("app",code);
            ret = code;
            iret = 6;
            return iret;
        }
        else
            return 0;
    }
    static int parseLogin(QString str,QString &ret)
    {
        int          iret = 0;
        QDomDocument dom;

        ret = "";
        if ( !dom.setContent(str))
            return CMD_ERROR;
        QDomElement  elem = dom.documentElement();
        if (elem.isNull())
            return CMD_ERROR;
        QString app = elem.attribute("app","");
        QString usr = elem.attribute("user","");
        QString code = elem.attribute("code","");

        if ( !app.isEmpty() )
        {
            Session::Instance()->setAppName(app);
            qDebug()<<"app:"<<app;
        }
        //由用户决定是否同意启动
        if (code.isEmpty())
        {
            QString str = LOCAL("是否允许 '")+app + LOCAL("' 启动?");
            //int iret = QMessageBox::information(MainDialog::Instance()->getFloatDlg(),LOCAL("通知"),str,
            //                         QMessageBox::YesAll);
            HWND wnd = MainDialog::Instance()->getFloatDlg()->winId();
            if (MessageBox(wnd,str.toStdWString().data(),TEXT("Warning"),MB_YESNO) == IDYES)
            //if(iret == QMessageBox::Yes)
            {
                ret = "<userAuth>" + Session::Instance()->getJID().split("@").at(0) + "</userAuth>";
            }else
            {
                ret = "<userAuth>error</userAuth>";
            }
        }else if(code.compare(Session::Instance()->getCode("app")) == 0)
        {
            //认证成功
            ret = "<userAuth>" + Session::Instance()->getJID().split("@").at(0) + "</userAuth>";

        }else ret = "<userAuth>error</userAuth>";
        iret = 1;
        return iret;
    }

    ///
    /// \brief parsePing
    /// \param str
    /// \return
    ///
    ///解析应用程序发送的ping命令，用于单点登录
    ///
    static int parsePing(char *str,QString &info)
    {
        QString qstr = QString::fromLocal8Bit(str);
        if ( qstr.indexOf("ping") < 0)
            return CMD_ERROR;
        QDomDocument doc;
        if( !doc.setContent(qstr))
            return CMD_ERROR;
        QDomElement elem = doc.documentElement();
        if ( elem.isNull() )
            return CMD_ERROR;
        QString app = elem.attribute("app");
        sprintf(str,app.toLocal8Bit().data());
        QString tipstr = LOCAL("是否允许 '")+app + LOCAL("' 登录?");
        info = tipstr;
        return CMD_PING;

        /*
        HWND wnd = MainDialog::Instance()->getFloatDlg()->winId();
        if (MessageBox(wnd,tipstr.toStdWString().data(),TEXT("Warning"),MB_YESNO) == IDYES)
            return CMD_PING;
        else
            return CMD_ERROR;
        */
    }

    static QString id_;
};


#endif // COMMANDPARSE_H
