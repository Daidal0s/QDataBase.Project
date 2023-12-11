#pragma once
#include "stdafx.h"

using Orm::Tiny::Model;

class TaskStatusConsumer final : public Model<TaskStatusConsumer>, public Fillable<TaskStatusConsumer>
{
    friend Fillable;
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"task_status_consumer"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;
    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"TaskStatus", "NEED2FILL"},
        {"Description", "NEED2FILL"},
    };

    inline static QStringList u_fillable {
        "TaskStatus",
        "Description",
    };
};