#include "qipcmemory.h"
#include "utils/defines.h"

#include <QDebug>

QIPCMemory::QIPCMemory(QObject *parent,QString name) : QObject(parent),m_name(name)
{
    if ( m_name.isEmpty() )
    {
        m_name = "desktop";
    }
    m_mem = new QSharedMemory(m_name);
    if ( !m_mem->create(SHARE_MEM_SIZE))
    {
        if(!m_mem->attach())
        {
            qDebug()<<LOCAL("无法创建及添加共享内存");
        }
    }

}

QIPCMemory::~QIPCMemory()
{
    delete m_mem;
}

void QIPCMemory::Write(const QString &data)
{
    char *pdata = NULL;
    m_mem->lock();
    pdata = static_cast<char*>(m_mem->data());
    strncpy(pdata,data.toLocal8Bit().data(),data.toLocal8Bit().length()+1);
    m_mem->unlock();
}

QString QIPCMemory::Read()
{
    m_mem->lock();
    const char *pdata = static_cast<const char*>(m_mem->constData());
    m_mem->unlock();
    return  QString::fromLocal8Bit(pdata);

}
