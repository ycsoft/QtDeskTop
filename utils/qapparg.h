#ifndef QAPPARG_H
#define QAPPARG_H

#include <QObject>
#include <QStringList>

class QAppArg : public QObject
{
    Q_OBJECT
public:

    int     &argCount()
    {
        return m_count;
    }

    QStringList &argList()
    {
        return m_arglist;
    }

    static QAppArg &ref()
    {
        static QAppArg app;
        return app;
    }

signals:

public slots:
private:
    explicit QAppArg(QObject *parent = 0);

    int      m_count;
    QStringList  m_arglist;
};

#endif // QAPPARG_H
