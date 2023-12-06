#ifndef WIDGET_H
#define WIDGET_H

#pragma once
#include "stdafx.h"
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
    std::shared_ptr<Dev> dev;

    std::unique_ptr<QSqlRelationalTableModel> m_employees;
    std::unique_ptr<QSqlRelationalTableModel> m_custasks;
    std::unique_ptr<QSqlRelationalTableModel> m_contasks;
private slots:
    void on_cb_model_currentIndexChanged(int index);

    void on_pb_submitChanges_clicked();

    void on_pb_saveTable_clicked();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
