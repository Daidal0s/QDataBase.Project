#pragma once
#include "stdafx.h"
#include "fillable.h"

using Orm::Tiny::Model;

class LegalForm final : 
    public Model<LegalForm>, 
    public Fillable<LegalForm>
{
    friend Fillable;
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"legal_forms"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;
    bool u_timestamps = false;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"LegalFormName", "NEED2FILL"},
    };
    
    inline static QStringList u_fillable {
        "LegalFormName",
    };
};