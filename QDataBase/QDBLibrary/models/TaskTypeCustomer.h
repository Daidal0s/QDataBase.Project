#pragma once
#include "orm/tiny/model.hpp"
#include <orm/schema.hpp>
#include <orm/schema/blueprint.hpp>

using Orm::Tiny::Model;

class TaskTypeCustomer final : public Model<TaskTypeCustomer>
{
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"task_type_customer"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"TaskType", "NewType"},
        {"Description", "New description"},
    };
    inline static QStringList u_fillable {
        "TaskType",
        "Description",
    };
};