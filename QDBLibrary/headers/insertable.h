#pragma once
#include "stdafx.h"

template <class Model>
class Insertable
{
friend Model;
public:
    inline void insert(const &QList<QVector> dataToInsert)
    {
        Model::create();
    }
};