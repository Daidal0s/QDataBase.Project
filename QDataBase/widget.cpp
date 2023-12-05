#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{

    ui->setupUi(this);

    DB::connectEagerly("mysql");

    if (!DB::connection("mysql").isOpen())
    {
        setWindowTitle("SHIT!");
    }
    else
        setWindowTitle("OK!");

    auto qdb = QSqlDatabase::addDatabase("QMYSQL");
    qdb.setHostName("127.0.0.1");
    qdb.setPort(3306);
    qdb.setUserName("qdb");
    qdb.setPassword("t3ngentoppagur3nlag4nn");
    qdb.setDatabaseName("QDB");

    qdb.open();

    m_employees = new QSqlRelationalTableModel();
    m_employees->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_employees->setTable("employees");
    m_employees->setRelation(0, QSqlRelation("user_data", "Login", "Login"));
    m_employees->setRelation(7, QSqlRelation("employee_status", "id", "EmployeeStatus"));
    m_employees->select();

    m_contasks = new QSqlRelationalTableModel();
    m_contasks->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_contasks->setTable("consumers_tasks");
    m_contasks->select();

    m_custasks = new QSqlRelationalTableModel();
    m_custasks->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_custasks->setTable("customers_tasks");
    m_custasks->select();
    
#ifdef DEV_BUILD
    qDebug() << Project::all().size() << " " << Project::first()->toVector().toList().size();

    if (qdb.isOpen())
    {
        // tablem->setQuery(empp);

        ui->tv_sql->setModel(m_employees);
        ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tv_sql->resizeColumnsToContents();
        ui->tv_sql->setItemDelegateForColumn(7, new QSqlRelationalDelegate(m_employees));
        ui->tv_sql->hideColumn(0);
    }
#endif
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_cb_model_currentIndexChanged(int index)
{
    switch (index)
    {
    default:
        break;
    case 0:
        ui->tv_sql->setModel(m_employees);
        ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tv_sql->resizeColumnsToContents();
        break;
    case 1:
        ui->tv_sql->setModel(m_contasks);
        ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tv_sql->resizeColumnsToContents();
        break;
    case 2:
        ui->tv_sql->setModel(m_custasks);
        ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tv_sql->resizeColumnsToContents();
        break;
    }
}


void Widget::on_pb_submitChanges_clicked()
{
    ui->tv_sql->model()->submit();

    switch (ui->cb_model->currentIndex())
    {
    default:
        break;
    case 0:
        m_employees->submitAll();
        break;
    case 1:
        m_contasks->submitAll();
        break;
    case 2:
        m_custasks->submitAll();
        break;
    }
}

