#pragma once
#include "orm/tiny/model.hpp"
#include <orm/schema.hpp>
#include <orm/schema/blueprint.hpp>
#include "UserData.h"
#include "ProjectStatus.h"

using Orm::Tiny::Model;

class UserData;
class ProjectStatus;

class Project final : public Model<Project,UserData,ProjectStatus>
{
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
        return hasMany<UserData>("StatusID","id");
    }
private:
    QString u_connection {"mysql"};
    QString u_table {"projects"};
    QString u_primaryKey {"ProjectID"};

    bool u_incrementing = true;
    bool u_timestamps = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"added_on", QDateTime::currentDateTime()},
    };
    inline static QStringList u_fillable {
        "ProjectID",
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