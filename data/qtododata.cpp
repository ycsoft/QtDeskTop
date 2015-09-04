#include "qtododata.h"

#include <lua.hpp>

#include <rapidjson.h>
#include <rapidjson/document.h>

QToDoData::QToDoData()
{

}


QString QToDoData::getData(QString host, QString db, QString usr, QString pwd)
{
    char buf[1024] = {0};
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L,"lua\\getResult.lua");
    lua_getglobal(L,"getResult");
    lua_pushstring(L,host.toLocal8Bit().data());
    lua_pushstring(L,db.toLocal8Bit().data());
    lua_pushstring(L,usr.toLocal8Bit().data());
    lua_pushstring(L,pwd.toLocal8Bit().data());
    lua_call(L,4,1);
    strncpy(buf,lua_tostring(L,-1),1023);
    lua_pop(L,1);

    return QString::fromUtf8(buf);
}
