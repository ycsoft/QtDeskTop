#ifndef QTODODATA_H
#define QTODODATA_H

#include <QStringList>
#include <lua.hpp>

class QToDoData
{
public:
    ~QToDoData();

    static QToDoData& ref()
    {
        static QToDoData todoData;
        return todoData;
    }
    QToDoData&  appendAll(const QString &str)
    {
        m_allList.append(str);
        return *this;
    }
    void setAll(const QStringList &lst)
    {
        int i = 0;
        for ( ; i<lst.count(); ++i )
        {
            appendAll(lst.at(i));
        }
    }

    QToDoData&  appendToDo(const QString &str)
    {
        m_todoList.append(str);
        return *this;
    }
    void setToDo(const QStringList &lst)
    {
        int i = 0;
        for ( ; i<lst.count(); ++i )
        {
            appendToDo(lst.at(i));
        }
    }

    QToDoData&  appendDone(const QString &str)
    {
        m_doneList.append(str);
        return *this;
    }
    void setDone(const QStringList &lst)
    {
        int i = 0;
        for ( ; i<lst.count(); ++i )
        {
            appendDone(lst.at(i));
        }
    }
    QString  getData(QString host, QString db,QString usr,QString pwd);

    QStringList &   getAll()
    {
        return m_allList;
    }
    QStringList &   getToDo()
    {
        return m_todoList;
    }
    QStringList &   getDone()
    {
        return m_doneList;
    }

private:
    QToDoData();

    QStringList         m_allList;
    QStringList         m_todoList;
    QStringList         m_doneList;
    lua_State           *m_Lua;
    char                *m_buf;
};

#endif // QTODODATA_H
