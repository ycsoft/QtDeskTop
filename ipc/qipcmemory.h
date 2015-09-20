#ifndef QIPCMEMORY_H
#define QIPCMEMORY_H

#include <QObject>
#include <QString>
#include <QSharedMemory>

class QIPCMemory : public QObject
{
    Q_OBJECT
public:
    enum Mode{MdRead,MdWrite,MdReadWrite};
    explicit QIPCMemory(QObject *parent = 0,QString name = "");
    ~QIPCMemory();

    void    Write(const QString &data);
    QString Read();
signals:

public slots:
private:
    QString             m_name;
    QSharedMemory       *m_mem;
    int                 m_mode;
};

#endif // QIPCMEMORY_H
