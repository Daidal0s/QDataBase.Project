#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include "stdafx.h"

class DBConnectionData;

class DBConnection
{
private:
    QSharedDataPointer<DBConnectionData> data;
    QSqlDatabase qdb;
public:
    DBConnection();
    ~DBConnection();
public:
    DBConnection(const DBConnection &);
    DBConnection &operator=(const DBConnection &);
public:
    QSqlDatabase getDB() const;
};

inline DBConnection dbConnection;

#endif // DBCONNECTION_H