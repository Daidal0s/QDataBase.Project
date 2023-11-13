#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QMYSQL");

    sdb.setHostName("localhost");
    sdb.setPort(3306);
    sdb.setUserName("qt");
    sdb.setPassword("root");

    if (!sdb.open()) {
        setWindowTitle("SHIT!");
    }
    else
        setWindowTitle("OK!");
}

Widget::~Widget()
{
    delete ui;
}