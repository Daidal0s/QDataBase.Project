#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include "stdafx.h"
#include "dbconnection.h"
#include "login.h"
#include "dev.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSharedPointer<Dev> w_dev;

    QList<QString> tableNames;
    QVector<QSharedPointer<QSqlRelationalTableModel>> modelVector;

    // QSharedPointer<QSqlRelationalTableModel> m_employees;                    TODO: DELETE
    // QSharedPointer<QSqlRelationalTableModel> m_custasks;
    // QSharedPointer<QSqlRelationalTableModel> m_contasks;

private slots:
    void on_cb_model_currentIndexChanged(int index);
    void on_pb_submitChanges_clicked();
    void on_pb_saveTable_clicked();
private:
    Ui::MainWindow *ui;
    void clearHidden(const QSqlRelationalTableModel *model);
};
#endif // MAINWINDOW_H