#pragma once
#include "stdafx.h"
#include "Role.h"

using Orm::Tiny::Model;

class UserData final : 
    public Model<UserData,Role>, 
    public Fillable<UserData>
{
    friend Fillable;
    friend Model;
    using Model::Model;
public:
    std::unique_ptr<HasMany<UserData, Role>>
    role()
    {
        return hasMany<Role>("RoleID", "id");
    }
private:
    QString u_connection {"mysql"};
    QString u_table {"user_data"};
    QString u_primaryKey {"Login"};

    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"Login", QVariant(QRandomGenerator::global()->generate() % 1000).toString()},
        {"Password","NEED2FILL"},
        {"RoleID",""},
    };

    inline static QStringList u_fillable {
        "Login",
        "Password",
        "RoleID",
    };

    QHash<QString, RelationVisitor> u_relations {
        {"role", [](auto &v) { v(&UserData::role); }}
    };
};