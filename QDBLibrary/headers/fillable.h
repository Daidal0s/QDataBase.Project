#pragma once
#include "stdafx.h"

template <class T>
class Fillable
{
friend T;
public:
    static QStringList getFillableList()
    {
        return T::u_fillable;
    }
};