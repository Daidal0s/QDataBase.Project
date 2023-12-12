#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "stdafx.h"
#include "mainwindow.h"
#include "login.h"
#include "dbconnection.h"
#ifdef DEV_BUILD
#include "dev.h"
#endif

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
    QSharedPointer<MainWindow> mainWindow;
#ifdef DEV_BUILD
    QSharedPointer<Dev> w_dev;
#endif
public:
    QString getLogin() const;
    Login::ROLE getRole() const;
};

#endif // LOGINWINDOW_H
