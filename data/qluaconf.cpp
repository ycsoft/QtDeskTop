#include "qluaconf.h"

#include <QFile>
#include <QSettings>

QLuaConf::QLuaConf(QObject *parent) : QObject(parent)
{
    int res;
    m_lua = luaL_newstate();
    luaL_openlibs(m_lua);
    //luaL_loadfile(m_lua,"lua/appset.lua");
    res = luaL_dofile(m_lua,"lua/appset.lua");
    if ( res != 0 )
    {
        qDebug()<<"error";
    }

    qRegisterMetaType<SrvList>("SrvList");
}

QLuaConf::~QLuaConf()
{
    lua_close(m_lua);
}

QString QLuaConf::getString(QString key)
{
    lua_getglobal(m_lua,key.toStdString().c_str());
    QString res = luaL_checkstring(m_lua,-1);
    lua_pop(m_lua,1);
    return res;
}
int QLuaConf::getInteger(QString key)
{
    lua_getglobal(m_lua,key.toStdString().c_str());
    int res = luaL_checkinteger(m_lua,-1);
    return res;
}
QStringList QLuaConf::getSrvList(QString key)
{
    QStringList res;
    lua_getglobal(m_lua,key.toStdString().c_str());
    if ( lua_istable(m_lua,-1))
    {
        qDebug()<<"Is Table";
    }
    int it = lua_gettop(m_lua);
    lua_pushnil(m_lua);
    it  = 1;
    while( 0!= lua_next(m_lua,it))
    {
        srvconf conf;
        conf.key = QString::fromLocal8Bit(luaL_checkstring(m_lua,-2));
        conf.value = QString::fromLocal8Bit(luaL_checkstring(m_lua,-1));
        res.push_back(conf.key + ":" + conf.value);
        lua_pop(m_lua,1);
    }
    lua_pop(m_lua,1);
    return res;
}
QString QLuaConf::getSrvJson(QString key)
{
    QString res;
    lua_getglobal(m_lua,key.toStdString().c_str());
    const char *cval = luaL_checkstring(m_lua,-1);
    lua_pop(m_lua,1);
    res = QString::fromUtf8(cval);
    return res;
}

void QLuaConf::setValue(QString key, QString value)
{
    QSettings set;
    set.setValue(key,value);
}
QString QLuaConf::getValue(QString key)
{
    QSettings set;
    return set.value(key,"").toString();
}
