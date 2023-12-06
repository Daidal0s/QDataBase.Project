#ifndef WIDGET_H
#define WIDGET_H

#pragma once
#include "stdafx.h"
#include "TableTemplate.h"
#include "dev.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QSqlDatabase qdb;
    Dev* dev;

    // QEmployee *testTable = new QEmployee(this);                  // TODO: DELETE THIS LINE

    QSqlRelationalTableModel* m_employees;
    QSqlRelationalTableModel* m_custasks;
    QSqlRelationalTableModel* m_contasks;
private slots:
    void on_cb_model_currentIndexChanged(int index);

    void on_pb_submitChanges_clicked();

    void on_pb_saveTable_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
