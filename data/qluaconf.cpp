#include "qluaconf.h"

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
QList<QLuaConf::srvconf> QLuaConf::getSrvList(QString key)
{
    QList<QLuaConf::srvconf> res;
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
        QLuaConf::srvconf conf;
        conf.key = QString::fromLocal8Bit(luaL_checkstring(m_lua,-2));
        conf.value = QString::fromLocal8Bit(luaL_checkstring(m_lua,-1));
        res.push_back(conf);
        lua_pop(m_lua,1);
    }
    lua_pop(m_lua,1);
    return res;
}
