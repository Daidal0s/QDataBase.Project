#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include "stdafx.h"
#include "dbconnection.h"
#include "login.h"
#include "workpie.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    
    QString _userName;
    Login::ROLE _userRole;
    QStringList _tableNamesToFilter;
    
    QList<QString> _tableNamesList;
    QStringList _namesForFill;
    QMap<QString, int> _tableNames;
    QVector<Orm::Tiny::AttributeItem> _dataToFill;

    QMap<QString, QStringList> _tablesAndFillables; 

    QVector<QSharedPointer<QTextEdit>> _fillableFields; 
    QVector<QSharedPointer<QSqlRelationalTableModel>> _modelVector;

    QSharedPointer<QSqlRelationalTableModel> _currentModel;
private:
    void setFilterTableNames();
    QStringList getRemoveColumn() const;
    void clearHidden();
    void setRelations();
    void setTablesAndFillables();
    void setFillFields(const QSqlRelationalTableModel *model);
    void printFillableFields();
private slots:
    void on_cb_model_currentIndexChanged(int index);
    void on_pb_submitChanges_clicked();
    void on_pb_createRecord_clicked();
private slots:
    void on_aData_in_diagrams_triggered();
    void on_actionTo_csv_triggered();
    void on_pb_remove_clicked();
public:
    MainWindow(const QString &userName = "admin", Login::ROLE userRole = Login::ROLE::ADMIN, QMainWindow *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
