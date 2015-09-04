#include "hfpgsql.h"
#include <sstream>

HFPGSql::HFPGSql():_conn(NULL),_result(NULL)
{
    _configure.connected = false;
}

HFPGSql::~HFPGSql()
{

    if ( NULL != _result )
        PQclear(_result);
    if ( NULL != _conn )
        PQfinish(_conn);
}

bool HFPGSql::connectDB(PGConfigure *config)
{
    ostringstream ostr;
    _configure = (*config);
    //memcpy(&_configure,config,sizeof(PGConfigure));
    ostr<<"hostaddr="<<config->host.c_str()<<" port="<<config->port
        <<" dbname="<<config->dbname.c_str()<<" user="<<config->usr
          <<" password="<<config->pwd;
    string connstr = ostr.str();

    _conn = PQconnectdb(connstr.c_str());

    if ( CONNECTION_BAD != PQstatus(_conn) )
    {
        _configure.connected = true;

        return true;
    }else
    {
        _configure.connected = false;
        return false;
    }

}

PGresult * HFPGSql::querySQL(string sql)
{
    if ( !_configure.connected )
        return NULL;
    PGresult *res = PQexec(_conn,sql.c_str());

    _result = res;
    return res;
}

int HFPGSql::getRecordCount()
{
    return PQntuples(_result);
}

int HFPGSql::getColumnCount()
{
    return PQnfields(_result);
}

string HFPGSql::fieldName(int column)
{
    int columns = PQnfields(_result);
    if ( column >= columns )
        return "";
    return string(PQfname(_result,column));
}

string HFPGSql::fieldValue(int row, int col)
{
    return PQgetvalue(_result,row,col);
}
