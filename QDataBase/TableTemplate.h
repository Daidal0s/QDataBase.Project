#pragma once
#include "stdafx.h"
#include <QComboBox>
#include <QAbstractTableModel>

const int ROWS = Project::all().size();


class QEmployee : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QEmployee(QObject *parent = nullptr);
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
//     bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
//     Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    QList<Employee> m_table;
// signals:
//     void editCompleted(const QString &);
};


// bool QEmployee::setData(const QModelIndex &index, const QVariant &value, int role)
// {
//     if (role == Qt::EditRole) {
//         if (!checkIndex(index))
//             return false;
//         //save value from editor to member m_gridData
//         m_gridData[index.row()][index.column()] = value.toString();
//         //for presentation purposes only: build and emit a joined string
//         QString result;
//         for (int row = 0; row < ROWS; row++) {
//             for (int col= 0; col < COLS; col++)
//                 result += m_gridData[row][col] + ' ';
//         }
//         emit editCompleted(result);
//         return true;
//     }
//     return false;
// }

// Qt::ItemFlags QEmployee::flags(const QModelIndex &index) const
// {
//     return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
// }