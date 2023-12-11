#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include "stdafx.h"
#include "dbconnection.h"
#include "login.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Login::ROLE _userRole;
    QList<QString> _namesOfFillableFields;
    QVector<QSharedPointer<QTextEdit>> _fillableFields; 
    QList<QString> _tableNames;
    // QMap<QString, > asd; 
    QVector<QSharedPointer<QSqlRelationalTableModel>> _modelVector;
private:
    void clearHidden(const QSqlRelationalTableModel *model);
    void fillFields(const QSqlRelationalTableModel *model);
    void printFillableFields();
private slots:
    void on_cb_model_currentIndexChanged(int index);
    void on_pb_submitChanges_clicked();
private slots:
    void on_actionTo_csv_triggered();
public:
    MainWindow(Login::ROLE userRole = Login::ROLE::DEV, QMainWindow *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
