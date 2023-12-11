#pragma once
#include "stdafx.h"
#include "Project.h"
#include "UserData.h"

using Orm::Tiny::Model;

class Project;
class UserData;

class ProjectRelatedEmployees final : public Model<ProjectRelatedEmployees,Project,UserData>, public Fillable<ProjectRelatedEmployees>
{
    friend Fillable;
    friend Model;
    using Model::Model;
public:
    std::unique_ptr<HasMany<ProjectRelatedEmployees, Project>>
    project()
    {
        return hasMany<Project>("ProjectID", "ProjectID");
    }

    std::unique_ptr<HasMany<ProjectRelatedEmployees, UserData>>
    employee()
    {
        return hasMany<UserData>("Employee", "Login");
    }
private:
    QString u_connection {"mysql"};
    QString u_table {"projects_employees"};
    bool u_timestamps = false;

    inline static QStringList u_fillable {
        "ProjectID",
        "Employee",
    };

    QHash<QString, RelationVisitor> u_relations {
        {"project", [](auto &v) { v(&ProjectRelatedEmployees::project); }},
        {"employee", [](auto &v) { v(&ProjectRelatedEmployees::employee); }},
    };
};