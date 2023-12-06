#ifndef DEV_H
#define DEV_H

#include <QDialog>
#include "stdafx.h"

namespace Ui {
class Dev;
}

class Dev : public QDialog
{
    Q_OBJECT

public:
    explicit Dev(QWidget *parent = nullptr);
    ~Dev();

private slots:
    void on_pb_create_clicked();

    void on_pb_testDB_clicked();

    void on_pb_fillSmol_clicked();

    void on_pb_fillAll_clicked();
private:
    Ui::Dev *ui;
};

#endif // DEV_H
