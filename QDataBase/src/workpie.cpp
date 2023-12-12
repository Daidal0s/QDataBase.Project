#include "workpie.h"
#include "ui_workpie.h"


WorkPie::WorkPie(QMap<QString, int> employeeData, QWidget *parent)
    : QDialog(parent), ui(new Ui::WorkPie), _employeeData(employeeData)
{
    ui->setupUi(this);

    auto series = new QPieSeries;

    auto names = _employeeData.keys();
    for (int iii = 0; iii < names.size(); ++iii)
    {
        qDebug() << _employeeData[names.at(iii)];
        series->append(names.at(iii), _employeeData[names.at(iii)]);
        series->slices().at(iii)->setLabelVisible();
    }

    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Most Profitable Employees");
    chart->legend()->show();

    ui->gv_charter->setChart(chart);
}

WorkPie::~WorkPie()
{
    delete ui;
}
