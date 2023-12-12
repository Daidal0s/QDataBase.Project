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

#ifdef DEV_BUILD
    w_dev = QSharedPointer<Dev>(new Dev(this));
    w_dev->show();
#endif
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pb_login_clicked()
{
    ui->lb_info->clear();

    auto userData = UserData::select();

    _login = ui->le_login->text();
    QString password = ui->le_password->text();
   
    if (userData->whereKey(_login).doesntExist())
    {
        ui->lb_info->setText("User doesn't exists! Try again");
        return;
    }

    if (userData->whereKey(_login).whereEq("Password",password).doesntExist())
    {
        ui->lb_info->setText("Wrong data! Try again");
        return;
    }

    _userRole = Login::setLogin(userData->whereKey(_login).pluck("RoleID").at(0).toInt());

    mainWindow = QSharedPointer<MainWindow>(new MainWindow(_login, _userRole));
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

