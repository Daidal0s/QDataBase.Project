#include "TableTemplate.h"

QEmployee::QEmployee(QObject *parent)
    : QAbstractTableModel(parent), m_table (Employee::all().toList())
{ }

int QEmployee::rowCount(const QModelIndex & /*parent*/) const
{
   return Employee::all().size();
}

int QEmployee::columnCount(const QModelIndex & /*parent*/) const
{
    return Employee::first()->toVector().size();
}

QVariant QEmployee::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            qDebug() << Employee::all().takeAt(index.row()).getRelationValue<UserData, Orm::One>("userData");
            return Employee::all().takeAt(index.row()).userData()->getParentKey();
            break;
        default:
            return m_table.at(index.row()).toVector().at(index.column()).value;
            break;
        }
    }
    return QVariant();
}