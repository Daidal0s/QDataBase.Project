#pragma once
#include "stdafx.h"
#include "fillable.h"


using Orm::Tiny::Model;

class EmployeePosition final : 
    public Model<EmployeePosition>, 
    public Fillable<EmployeePosition>
{
    friend Fillable;
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"employee_positions"};
    QString u_primaryKey {"id"};
    
    bool u_incrementing = true;
    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"PositionName", "NEED2FILL"},
        {"Description", "NEED2FILL"},
    };

    inline static QStringList u_fillable {
        "PositionName",
        "Description",
    };
};