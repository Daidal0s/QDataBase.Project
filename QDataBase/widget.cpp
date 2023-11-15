#include "widget.h"
#include "ui_widget.h"
#include <QSqlError>
#include <QDebug>
#include "QDBLibrary.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QMYSQL");
    sdb.setDatabaseName("QDB");
    sdb.setHostName("127.0.0.1");
    sdb.setPort(3306);
    sdb.setUserName("qdb");
    sdb.setPassword("t3ngentoppagur3nlag4nn");

    auto qquery = QSqlQuery("use QDB", sdb);

    sdb.open();

    if (!DB::connection("mysql").isOpen()) {
        setWindowTitle("SHIT!");
        qDebug() << qquery.lastError().text();
    }
    else
        setWindowTitle("OK!");
}

Widget::~Widget()
{
    delete ui;
}