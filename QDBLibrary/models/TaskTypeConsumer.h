#pragma once
#include "stdafx.h"
#include "fillable.h"


using Orm::Tiny::Model;

class TaskTypeConsumer final : 
    public Model<TaskTypeConsumer>, 
    public Fillable<TaskTypeConsumer>
{
    friend Fillable;
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"task_type_consumer"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;
    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"TaskType", "NEED2FILL"},
        {"Description", "NEED2FILL"},
    };
    
    inline static QStringList u_fillable {
        "TaskType",
        "Description",
    };
};