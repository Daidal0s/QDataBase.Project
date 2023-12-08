#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "stdafx.h"
#include "mainwindow.h"
#include "login.h"
#include "dbconnection.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT
private:
    Ui::LoginWindow *ui;
private:
    QString _login;
    Login::ROLE _userRole;
private slots:
    void on_pb_login_clicked();
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
public:
    MainWindow *mainWindow;
public:
    QString getLogin() const;
    Login::ROLE getRole() const;
};

#endif // LOGINWINDOW_H
