#include "dbconnection.h"

class DBConnectionData : public QSharedData
{
public:
};

DBConnection::DBConnection()
    : data(new DBConnectionData)
{
    qdb = QSqlDatabase::addDatabase("QMYSQL");
    qdb.setHostName("127.0.0.1");
    qdb.setPort(3306);
    qdb.setUserName("qdb");
    qdb.setPassword("t3ngentoppagur3nlag4nn");
#ifdef DEV_BUILD
    qdb.setDatabaseName("Test");
#else
    qdb.setDatabaseName("QDB");
#endif

    qdb.open();

    DB::connectEagerly("mysql");
}

DBConnection::DBConnection(const DBConnection &rhs)
    : data{rhs.data}
{}

DBConnection &DBConnection::operator=(const DBConnection &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QSqlDatabase DBConnection::getDB() const
{
    return qdb;
}

DBConnection::~DBConnection() {}
