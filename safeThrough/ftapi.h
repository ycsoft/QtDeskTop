#ifndef FTAPI_H
#define FTAPI_H

#include <QObject>
#include <QFile>

class MySock;


class FTAPI : public QObject
{
    Q_OBJECT
public:
    enum    Mode{Upload,Download};
    explicit FTAPI(QObject *parent = 0);
    ~FTAPI();

    void     login(const char *id, const char *host, int port);
    void     close();
    void     sendFileRequest(const char *from,const char *to,const char *filename);
    void     rejectFile(const char *from, const char *to, const char *filename);
    void     resolveData(void **data);
    void     senddata(void* data,int len);
    void     downloadFile(const char *filename);
    MySock*  getSock(){return c_sock;}
    void     setFile(QFile *f) {m_file = f;}
    void     setFile(QString fn);
    QFile*   getFile() { return m_file;}
    void     setMode( Mode md ) { m_md = md;}
    Mode     getMode() const { return m_md;}

    static  FTAPI *Instance();

public slots:
    void    slotAgreeFileTrans(QString from ,QString to , QString filename);
signals:
    void    signalprogress(uint transed,uint total);
    void    signalFinished();
private:
    MySock  *c_sock;
    QFile   *m_file;
    Mode    m_md;
    static FTAPI *m_instance;
};

#endif // FTAPI_H
