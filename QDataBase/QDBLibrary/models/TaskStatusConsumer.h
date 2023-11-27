#pragma once
#include "orm/tiny/model.hpp"
#include <orm/schema.hpp>
#include <orm/schema/blueprint.hpp>

using Orm::Tiny::Model;

class TaskStatusConsumer final : public Model<TaskStatusConsumer>
{
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"task_status_consumer"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"TaskStatus", "NewStatus"},
        {"Description", "New description"},
    };
    inline static QStringList u_fillable {
        "TaskStatus",
        "Description",
    };
};