#pragma once
#include "stdafx.h"
#include "UserData.h"
#include "EmployeePosition.h"
#include "EmployeeStatus.h"

using Orm::Tiny::Model;

class UserData;
class EmployeePosition;
class EmployeeStatus;

class Employee final : public Model<Employee,UserData,EmployeePosition,EmployeeStatus>
{
    friend Model;
    using Model::Model;
public:
    std::unique_ptr<HasOne<Employee, UserData>>
    userData()
    {
        return hasOne<UserData>("AuthData", "Login");
    }

    std::unique_ptr<HasMany<Employee, EmployeePosition>>
    position()
    {
        return hasMany<EmployeePosition>("PositionID", "id");
    }

    std::unique_ptr<HasMany<Employee, EmployeeStatus>>
    status()
    {
        return hasMany<EmployeeStatus>("StatusID", "id");
    }
private:
    QString u_connection {"mysql"};
    QString u_table {"employees"};
    QString u_primaryKey {"AuthData"};

    bool u_timestamps = false;

    inline static QStringList u_fillable {
        "AuthData",
        "FIO",
        "PassportData",
        "BirthDay",
        "PositionID",
        "ContactDataNum",
        "ContactDataEMail",
        "StatusID",
    };

    QHash<QString, RelationVisitor> u_relations {
        {"userData", [](auto &v) { v(&Employee::userData); }},
        {"position", [](auto &v) { v(&Employee::position); }},
        {"status", [](auto &v) { v(&Employee::status); }},
    };
};