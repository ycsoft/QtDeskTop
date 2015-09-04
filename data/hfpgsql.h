#ifndef HFPGSQL_H
#define HFPGSQL_H


#include <libpq-fe.h>
#include <string>

using namespace std;

struct PGConfigure
{
    void operator = ( const PGConfigure &conf)
    {
        host = conf.host;
        dbname = conf.dbname;
        usr = conf.usr;
        pwd = conf.pwd;
        port = conf.port;
        connected = conf.connected;
    }
    PGConfigure()
    {
        port = 5432;
    }

    string host;
    string dbname;
    string usr;
    string pwd;
    int    port;
    bool   connected;
};

class HFPGSql
{
public:
    HFPGSql();
    ~HFPGSql();

    bool        connectDB(PGConfigure *config);

    PGresult    *querySQL(string sql);
    int         getRecordCount();
    int         getColumnCount();
    string      fieldName( int column );
    string      fieldValue( int row, int col);

private:
    PGConfigure     _configure;
    PGresult        *_result;
    PGconn          *_conn;
};

#endif // HFPGSQL_H
