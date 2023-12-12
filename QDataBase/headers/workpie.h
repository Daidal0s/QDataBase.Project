#ifndef WORKPIE_H
#define WORKPIE_H

#include "stdafx.h"

namespace Ui {
class WorkPie;
}

class WorkPie : public QDialog
{
    Q_OBJECT
public:
    explicit WorkPie(QMap<QString, int> employeeData = QMap<QString,int>(), QWidget *parent = nullptr);
    ~WorkPie();
private:
    QMap<QString, int> _employeeData;
    Ui::WorkPie *ui;
};

#endif // WORKPIE_H
