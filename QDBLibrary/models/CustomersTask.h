#pragma once
#include "stdafx.h"
#include "LegalForm.h"
#include "TaskTypeCustomer.h"
#include "TaskStatusCustomer.h"
#include "Project.h"

using Orm::Tiny::Model;

class LegalForm;
class TaskTypeCustomer;
class TaskStatusCustomer;
class Project;

class CustomersTask final : 
    public Model<CustomersTask,LegalForm,TaskTypeCustomer,TaskStatusCustomer,Project>, 
    public Fillable<CustomersTask>
{
    friend Fillable;
    friend Model;
    using Model::Model;
public:
    std::unique_ptr<HasMany<CustomersTask, LegalForm>>
    legalForm()
    {
        return hasMany<LegalForm>("LegalFormID","id");
    }

    std::unique_ptr<HasMany<CustomersTask, TaskTypeCustomer>>
    type()
    {
        return hasMany<TaskTypeCustomer>("TaskTypeID","id");
    }

    std::unique_ptr<HasMany<CustomersTask, TaskStatusCustomer>>
    status()
    {
        return hasMany<TaskStatusCustomer>("StatusID", "id");
    }

    std::unique_ptr<HasMany<CustomersTask, Project>>
    project()
    {
        return hasMany<Project>("RelatedProject", "ProjectID");
    }
private:
    QString u_connection {"mysql"};
    QString u_table {"customers_tasks"};
    QString u_primaryKey {"INN"};

    bool u_incrementing = true;
    bool u_timestamps = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"INN", QVariant(QRandomGenerator::global()->generate() % 1000).toString()},
        {"LegalFormID",""},
        {"Name","NEED2FILL"},
        {"Adress",""},
        {"TaskTypeID",""},
        {"Profitability",""},
        {"ContactDataNum",""},
        {"StatusID",""},
        {"RelatedProject",""},
        {"added_on", QDateTime::currentDateTime()},
    };

    inline static QStringList u_fillable {
        "INN",
        "LegalFormID",
        "Name",
        "Adress",
        "TaskTypeID",
        "Profitability",
        "ContactDataNum",
        "StatusID",
        "RelatedProject",
    };

    QHash<QString, RelationVisitor> u_relations {
        {"legalForm", [](auto &v) { v(&CustomersTask::legalForm); }},
        {"type", [](auto &v) { v(&CustomersTask::type); }},
        {"status", [](auto &v) { v(&CustomersTask::status); }},
        {"project", [](auto &v) { v(&CustomersTask::project); }},
    };
};