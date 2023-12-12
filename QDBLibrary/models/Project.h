#pragma once
#include "stdafx.h"
#include "UserData.h"
#include "ProjectStatus.h"

using Orm::Tiny::Model;

class UserData;
class ProjectStatus;

class Project final : 
    public Model<Project,UserData,ProjectStatus>, 
    public Fillable<Project>
{
    friend Fillable;
    friend Model;
    using Model::Model;
public:
    std::unique_ptr<HasMany<Project, UserData>>
    teamLeader()
    {
        return hasMany<UserData>("TeamLeader","Login");
    }
    
    std::unique_ptr<HasMany<Project, ProjectStatus>>
    status()
    {
        return hasMany<ProjectStatus>("StatusID","id");
    }
private:
    QString u_connection {"mysql"};
    QString u_table {"projects"};
    QString u_primaryKey {"ProjectID"};

    bool u_incrementing = true;
    bool u_timestamps = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"ProjectName","NEED2FILL"},
        {"TeamLeader",""},
        {"Description",""},
        {"Documentation",""},
        {"StatusID",""},
        {"added_on", QDateTime::currentDateTime()},
    };

    inline static QStringList u_fillable {
        "ProjectName",
        "TeamLeader",
        "Description",
        "Documentation",
        "StatusID",
    };

    QHash<QString, RelationVisitor> u_relations {
        {"teamLeader", [](auto &v) { v(&Project::teamLeader); }},
        {"status", [](auto &v) { v(&Project::status); }},
    };
};