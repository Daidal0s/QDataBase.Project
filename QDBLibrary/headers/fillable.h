#pragma once
#include "stdafx.h"

template <class Model>
class Fillable
{
friend Model;
public:
    static QStringList getFillableList()
    {
        return Model::u_fillable;
    }
};