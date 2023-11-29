#ifndef WIDGET_H
#define WIDGET_H

#pragma once
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void DEV_createDB();
    void DEV_testBD();
    void DEV_fillSomeTables();
    void DEV_fillAllTables();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
