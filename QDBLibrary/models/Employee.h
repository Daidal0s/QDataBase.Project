#pragma once
#include "stdafx.h"
#include "UserData.h"
#include "EmployeePosition.h"
#include "EmployeeStatus.h"

using Orm::Tiny::Model;

class UserData;
class EmployeePosition;
class EmployeeStatus;

class Employee final : 
    public Model<Employee,UserData,EmployeePosition,EmployeeStatus>, 
    public Fillable<Employee>
{
    friend Fillable;
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
    QString u_primaryKey {"id"};

    bool u_incrementing = true;
    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"AuthData",""},
        {"FIO","NEED2FILL"},
        {"PassportData","NEED2FILL"},
        {"BirthDay", QDateTime::currentDateTime()},
        {"PositionID",""},
        {"ContactDataNum","NEED2FILL"},
        {"ContactDataEMail","NEED2FILL"},
        {"StatusID",""},
        {"ComplitedTasks",0},
    };

    inline static QStringList u_fillable {
        "AuthData",
        "FIO",
        "PassportData",
        "BirthDay",
        "PositionID",
        "ContactDataNum",
        "ContactDataEMail",
        "StatusID",
        "ComplitedTasks",
    };

    QHash<QString, RelationVisitor> u_relations {
        {"userData", [](auto &v) { v(&Employee::userData); }},
        {"position", [](auto &v) { v(&Employee::position); }},
        {"status", [](auto &v) { v(&Employee::status); }},
    };
};