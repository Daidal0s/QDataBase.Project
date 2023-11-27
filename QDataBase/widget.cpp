#include "widget.h"
#include "ui_widget.h"
#include "QDBLibrary.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);

    DB::connectEagerly("mysql");

    if (!DB::connection("mysql").isOpen()) {
        setWindowTitle("SHIT!");
    }
    else
        setWindowTitle("OK!");

#ifdef DEV_BUILD
    QPushButton *btn = new QPushButton(this);
    btn->setText("CreateDB");
    connect(btn, SIGNAL(clicked()), SLOT(DEV_createDB()));

    QPushButton *btn2 = new QPushButton(this);
    btn2->setText("TestBD");
    btn2->move(10, 40);
    connect(btn2, SIGNAL(clicked()), SLOT(DEV_testBD()));
#endif
}

Widget::~Widget()
{
    delete ui;
}

void Widget::DEV_createDB()
{
    createDB();
}

void Widget::DEV_testBD()
{
    testModels();
}