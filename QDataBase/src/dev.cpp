#include "dev.h"
#include "ui_dev.h"

Dev::Dev(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dev)
{
    ui->setupUi(this);
}

Dev::~Dev()
{
    delete ui;
}

void Dev::on_pb_create_clicked()
{
    createDB();
}

void Dev::on_pb_testDB_clicked()
{
    testModels();
}

void Dev::on_pb_fillSmol_clicked()
{
    if (UserData::count() == 0)
    {
        auto role = Role::firstOrCreate(
            {
                {"RoleName", "User"},
            });

        auto auth = UserData::create(
            {
                {"Login", "pivo2323"},
                {"Password", "dochkaSuper"},
                {"RoleID", 1},
            });

        auto eplPos = EmployeePosition::firstOrCreate(
            {
                {"PositionName", "Genius"},
            });

        auto eplStatus = EmployeeStatus::firstOrCreate(
            {
                {"EmployeeStatus", "Alive"},
            });

        auto epl = Employee::create(
            {
                {"AuthData", "pivo2323"},
                {"FIO", "Zubenko Кирил Mefody"},
                {"PassportData", "22 81 337228"},
                {"BirthDay", QDate::currentDate()},
                {"PositionID", "1"},
                {"ContactDataNum", "+7 777 777 77 77"},
                {"ContactDataEMail", "mama@mama.su"},
                {"StatusID", "1"},
            });
    }
}

void Dev::on_pb_fillAll_clicked()
{
    fillDB(true);
}
