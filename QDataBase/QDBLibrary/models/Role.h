#pragma once
#include "stdafx.h"

using Orm::Tiny::Model;

class Role final : public Model<Role>
{
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"roles"};
    QString u_primaryKey {"id"};
    
    bool u_incrementing = true;
    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"RoleName", "NewRole"},
    };
    inline static QStringList u_fillable {
        "RoleName",
        "Description",
    };
};