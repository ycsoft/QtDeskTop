#ifndef MYLOCK_H
#define MYLOCK_H

#include <QObject>

class MyLock : public QObject
{
    Q_OBJECT
public:
    explicit MyLock(QObject *parent = 0);
    static MyLock *Instance();

    void   setLock(bool b)
    {
        c_canbesend = b;
    }
    bool   getLock()
    {
        return c_canbesend;
    }
    void  setTransed(int i)
    {
        c_transed = i;
    }
    int  getTransed()
    {
        return c_transed;
    }

signals:

public slots:
private:
    static MyLock  *c_lock;
    bool    c_canbesend;
    uint     c_transed;

};

#endif // MYLOCK_H
