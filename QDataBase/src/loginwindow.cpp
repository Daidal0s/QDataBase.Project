#include "loginwindow.h"
#include "ui_loginwindow.h"


LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    if (!DB::connection("mysql").isOpen() && !dbConnection.getDB().isOpen())
        this->setWindowTitle("SHIT!");
    else
        this->setWindowTitle("OK!");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pb_login_clicked()
{
    ui->lb_info->clear();

    _login = ui->le_login->text();

    auto userData = UserData::select();
    
    if (userData->whereKey(_login).doesntExist())
    {
        ui->lb_info->setText("User doesn't exists! Try again");
        return;
    }

    QString password = ui->le_password->text();

    if (userData->whereKey(_login).whereEq("Password",password).doesntExist())
    {
        ui->lb_info->setText("Wrong data! Try again");
        return;
    }

    switch (userData->whereKey(_login).pluck("RoleID").at(0).toInt())
    {
    case 1:
        _userRole = Login::ROLE::ADMIN;
        break;
    case 2:
        _userRole = Login::ROLE::DEV;
        break;
    case 3:
        _userRole = Login::ROLE::TEAMLEADER;
        break;
    default:
        break;
    }

    mainWindow = new MainWindow();

    this->hide();
    mainWindow->show();
}

QString LoginWindow::getLogin() const
{
    return _login;
}

Login::ROLE LoginWindow::getRole() const
{
    return _userRole;
}

