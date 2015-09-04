#include "qtododata.h"
#include "utils/defines.h"
#include "data/hfpgsql.h"
#include <lua.hpp>
#include <rapidjson.h>
#include <rapidjson/document.h>

QToDoData::QToDoData()
{
    m_Lua = luaL_newstate();
    luaL_openlibs(m_Lua);
    luaL_dofile(m_Lua,"lua\\getResult.lua");
    m_buf = new char[3*MB];
}

QToDoData::~QToDoData()
{
    lua_close(m_Lua);
    delete [] m_buf;
}

QString QToDoData::getData(QString host, QString db, QString usr, QString pwd)
{
    QString result;    
    memset(m_buf,0,3*MB);

    lua_getglobal(m_Lua,"getResult");
    lua_pushstring(m_Lua,host.toLocal8Bit().data());
    lua_pushstring(m_Lua,db.toLocal8Bit().data());
    lua_pushstring(m_Lua,usr.toLocal8Bit().data());
    lua_pushstring(m_Lua,pwd.toLocal8Bit().data());
    lua_call(m_Lua,4,1);
    const char *res = lua_tostring(m_Lua,-1);
    strncpy(m_buf,res,strlen(res));
    lua_pop(m_Lua,1);
    result = QString::fromUtf8(m_buf);

//    PGConfigure conf;
//    conf.host = "127.0.0.1";
//    conf.dbname = "fasp_yz";
//    conf.usr = "postgres";
//    conf.pwd = "postgres";
//    conf.port = 5432;
//    HFPGSql pg;
//    pg.connectDB(&conf);
//    pg.querySQL("select getbydate('c016','2015-01-01','');");
//    string value = pg.fieldValue(0,0);
//    result = QString::fromUtf8(value.c_str());
    return result;
}
