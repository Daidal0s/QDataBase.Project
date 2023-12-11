#pragma once
#include "stdafx.h"
#include "UserData.h"
#include "TaskTypeConsumer.h"
#include "TaskStatusConsumer.h"

using Orm::Tiny::Model;

class UserData;
class TaskTypeConsumer;
class TaskStatusConsumer;

class ConsumerTask final : public Model<ConsumerTask,UserData,TaskTypeConsumer,TaskStatusConsumer>, public Fillable<ConsumerTask>
{
    friend Fillable;
    friend Model;
    using Model::Model;
public:

public:
    std::unique_ptr<HasMany<ConsumerTask, TaskTypeConsumer>>
    taskType()
    {
        return hasMany<TaskTypeConsumer>("TaskTypeID", "id");
    }

    std::unique_ptr<HasMany<ConsumerTask, TaskStatusConsumer>>
    status()
    {
        return hasMany<TaskStatusConsumer>("StatusID", "id");
    }

    std::unique_ptr<HasMany<ConsumerTask, UserData>>
    employee()
    {
        return hasMany<UserData>("RelatedEmployee", "Login");
    }
private:
    QString u_connection {"mysql"};
    QString u_table {"consumers_tasks"};
    QString u_primaryKey {"TaskID"};

    bool u_incrementing = true;
    bool u_timestamps = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"FIO","NEED2FILL"},
        {"TaskTypeID",""},
        {"ContactDataNum","NEED2FILL"},
        {"RelatedEmployee",""},
        {"StatusID",""},
        {"added_on", QDateTime::currentDateTime()},
    };

    inline static QStringList u_fillable 
    {
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