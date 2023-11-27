#pragma once
#include "orm/tiny/model.hpp"
#include <orm/schema.hpp>
#include <orm/schema/blueprint.hpp>

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