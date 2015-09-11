#ifndef QLUACONF_H
#define QLUACONF_H

#include <QObject>
#include <lua.hpp>
#include <QDebug>
#include <QList>
#include <QStringList>


struct   srvconf
{
    QString key;
    QString value;
};

typedef QList<srvconf>  SrvList;

/**
 * @brief The QLuaConf class
 * 从LUA配置文件中读取应用程序的配置
 */
class QLuaConf : public QObject
{
    Q_OBJECT
public:
    explicit QLuaConf(QObject *parent = 0);
    ~QLuaConf();

signals:

public slots:
    /**
     * @brief getString
     * 获取字符串数据项
     * @param key：关键字 key = value
     * @return 字符串
     */
    QString  getString(QString key);
    /**
     * @brief getInteger
     * 获取整数数据项
     * @param key
     * @return
     */
    int      getInteger(QString key);
    QStringList   getSrvList(QString key);
    QString  getSrvJson(QString key);

    void     setValue(QString key, QString value);
    QString  getValue(QString key);
private:
    lua_State   *m_lua;
};

#endif // QLUACONF_H
