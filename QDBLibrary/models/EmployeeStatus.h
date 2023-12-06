#pragma once
#include "stdafx.h"
using Orm::Tiny::Model;

class EmployeeStatus final : public Model<EmployeeStatus>
{
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"employee_status"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;
    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"EmployeeStatus", "NewStatus"},
        {"Description", "New description"},
    };
    inline static QStringList u_fillable {
        "EmployeeStatus",
        "Description",
    };
};