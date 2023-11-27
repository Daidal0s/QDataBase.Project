#pragma once
#include "orm/tiny/model.hpp"
#include <orm/schema.hpp>
#include <orm/schema/blueprint.hpp>

using Orm::Tiny::Model;

class ProjectStatus final : public Model<ProjectStatus>
{
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"project_status"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;
    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"ProjectStatusName", "NewStatus"},
        {"Description", "New description"},
    };
    inline static QStringList u_fillable {
        "ProjectStatusName",
        "Description",
    };
};