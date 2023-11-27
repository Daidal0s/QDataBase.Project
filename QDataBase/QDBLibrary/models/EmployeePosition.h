#pragma once
#include "orm/tiny/model.hpp"
#include <orm/schema.hpp>
#include <orm/schema/blueprint.hpp>

using Orm::Tiny::Model;

class EmployeePosition final : public Model<EmployeePosition>
{
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"employee_positions"};
    QString u_primaryKey {"id"};
    
    bool u_incrementing = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"PositionName", "NewPosition"},
        {"Description", "Position Description"},
    };
    inline static QStringList u_fillable {
        "PositionName",
        "Description",
    };
};