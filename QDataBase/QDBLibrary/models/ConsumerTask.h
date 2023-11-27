#pragma once
#include "orm/tiny/model.hpp"
#include <orm/schema.hpp>
#include <orm/schema/blueprint.hpp>
#include "UserData.h"
#include "TaskTypeConsumer.h"
#include "TaskStatusConsumer.h"

using Orm::Tiny::Model;

class UserData;
class TaskTypeConsumer;
class TaskStatusConsumer;

class ConsumerTask final : public Model<ConsumerTask,UserData,TaskTypeConsumer,TaskStatusConsumer>
{
    friend Model;
    using Model::Model;
public:
    std::unique_ptr<HasMany<ConsumerTask, TaskTypeConsumer>>
    taskType()
    {
        return hasMany<TaskTypeConsumer>("TaskTypeID", "id");
    }

    std::unique_ptr<HasMany<ConsumerTask, TaskStatusConsumer>>
    status()
    {
        return hasMany<TaskTypeConsumer>("StatusID", "id");
    }

    std::unique_ptr<HasMany<ConsumerTask, UserData>>
    employee()
    {
        return hasMany<TaskTypeConsumer>("RelatedEmployee", "Login");
    }
private:
    QString u_connection {"mysql"};
    QString u_table {"consumers_tasks"};
    QString u_primaryKey {"TaskID"};

    bool u_incrementing = true;
    bool u_timestamps = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"added_on", QDateTime::currentDateTime()},
    };
    inline static QStringList u_fillable {
        "TaskID",
        "FIO",
        "TaskTypeID",
        "ContactDataNum",
        "RelatedEmployee",
        "StatusID",
    };

    QHash<QString, RelationVisitor> u_relations {
        {"taskType", [](auto &v) { v(&ConsumerTask::taskType); }},
        {"status", [](auto &v) { v(&ConsumerTask::status); }},
        {"employee", [](auto &v) { v(&ConsumerTask::employee); }},
    };
};