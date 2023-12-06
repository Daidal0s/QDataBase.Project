#pragma once
#include "stdafx.h"

using Orm::Tiny::Model;

class TaskStatusCustomer final : public Model<TaskStatusCustomer>
{
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"task_status_customer"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;
    bool u_timestamps = false;

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