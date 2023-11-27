#pragma once
#include "orm/tiny/model.hpp"
#include <orm/schema.hpp>
#include <orm/schema/blueprint.hpp>

using Orm::Tiny::Model;

class LegalForm final : public Model<LegalForm>
{
    friend Model;
    using Model::Model;
private:
    QString u_connection {"mysql"};
    QString u_table {"legal_forms"};
    QString u_primaryKey {"id"};

    bool u_incrementing = true;

    inline static const QVector<AttributeItem> u_attributes
    {
        {"LegalFormName", "New Form"},
    };
    inline static QStringList u_fillable {
        "LegalFormName",
    };
};