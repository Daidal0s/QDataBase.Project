#ifndef WIDGET_H
#define WIDGET_H

#pragma once
#include "stdafx.h"
#include "TableTemplate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QEmployee *testTable = new QEmployee(this);

private slots:
    void DEV_createDB();
    void DEV_testBD();
    void DEV_fillSomeTables();
    void DEV_fillAllTables();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
