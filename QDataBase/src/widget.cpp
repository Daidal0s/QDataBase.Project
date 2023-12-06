#include "widget.h"
#include "ui_widget.h"
#include "ui_dev.h"

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

    qdb = QSqlDatabase::addDatabase("QMYSQL");
    qdb.setHostName("127.0.0.1");
    qdb.setPort(3306);
    qdb.setUserName("qdb");
    qdb.setPassword("t3ngentoppagur3nlag4nn");
    qdb.setDatabaseName("QDB");

    qdb.open();

    if (Orm::Schema::hasTable("employees"))
    {
        m_employees = new QSqlRelationalTableModel();
        m_employees->setEditStrategy(QSqlTableModel::OnRowChange);
        m_employees->setTable("employees");
        m_employees->setJoinMode(QSqlRelationalTableModel::InnerJoin);
        m_employees->setRelation(5, QSqlRelation("employee_positions", "id", "PositionName"));
        m_employees->setRelation(8, QSqlRelation("employee_status", "id", "EmployeeStatus"));
        m_employees->select();
        qDebug() << m_employees->lastError();                           // TODO: DELETE THIS LINE
    }

    if (Orm::Schema::hasTable("consumers_tasks"))
    {
        m_contasks = new QSqlRelationalTableModel();
        m_contasks->setEditStrategy(QSqlTableModel::OnManualSubmit);
        m_contasks->setTable("consumers_tasks");
        m_contasks->setRelation(2, QSqlRelation("task_type_consumer", "id", "TaskType"));
        m_contasks->setRelation(5, QSqlRelation("task_status_consumer", "id", "TaskStatus"));
        m_contasks->select();
    }

    if (Orm::Schema::hasTable("customers_tasks"))
    {
        m_custasks = new QSqlRelationalTableModel();
        m_custasks->setEditStrategy(QSqlTableModel::OnManualSubmit);
        m_custasks->setTable("customers_tasks");
        m_custasks->select();
    }
    
#ifdef DEV_BUILD
    // qDebug() << Project::all().size() << " " << Project::first()->toVector().toList().size();       // TODO: DELETE THIS LINE

    dev = new Dev();
    // dev->show();

    this->hide();

    if (qdb.open() && Orm::Schema::hasTable("customers_tasks"))
    {
        this->show();
        ui->tv_sql->setModel(m_employees);
        ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tv_sql->resizeColumnsToContents();
        ui->tv_sql->setItemDelegate(new QSqlRelationalDelegate(ui->tv_sql));
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
        if (qdb.tables().contains(tr("employees")))
        {
            ui->tv_sql->setModel(m_employees);
            ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tv_sql->resizeColumnsToContents();
        }
        break;
    case 1:
        if (qdb.tables().contains(tr("consumers_tasks")))
        {
            ui->tv_sql->setModel(m_contasks);
            ui->tv_sql->hideColumn(0);
            ui->tv_sql->hideColumn(6);
            ui->tv_sql->hideColumn(7);
            ui->tv_sql->setItemDelegate(new QSqlRelationalDelegate(ui->tv_sql));
            ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tv_sql->resizeColumnsToContents();
        }
        break;
    case 2:
        if (qdb.tables().contains(tr("customers_tasks")))
        {
            ui->tv_sql->setModel(m_custasks);
            ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tv_sql->resizeColumnsToContents();
        }
        break;
    }
}


void Widget::on_pb_submitChanges_clicked()
{
    switch (ui->cb_model->currentIndex())
    {
    default:
        break;
    case 0:
        qDebug() << m_employees->submitAll();                       // TODO: DELETE DUBUG
        qDebug() << m_employees->lastError();
        break;
    case 1:
        qDebug() << m_contasks->submitAll();
        qDebug() << m_contasks->lastError();
        break;
    case 2:
        ui->horizontalLayout->addWidget(new Dev());
        m_custasks->submitAll();
        break;
    }
}

void Widget::on_pb_saveTable_clicked()
{
    QString csv_filepath = QDir::currentPath() + "/export.csv";

    QtCSV::StringData data;
    auto wtf = DB::qtQuery();
    QList<QList<QString>> wtf3;

    auto fillData = [](QSqlQuery &wtf, QList<QList<QString>> &wtf3, QtCSV::StringData &data)
    {
        QList<QString> wtf2;

        while (wtf.next())
        {
            for (int iii = 1;iii <= 8;++iii)
            {
                wtf2.push_back(wtf.value(iii).toString());
            }
            wtf3.push_back(wtf2);
            wtf2.clear();
        }

        for(int iii = 0; iii < wtf3.size(); ++iii)
        {
            data.addRow(wtf3.at(iii));
        }
    };

    switch (ui->cb_model->currentIndex())
    {
    default:
        break;
    case 0:
        wtf.exec((m_employees->query().executedQuery()));
        fillData(wtf, wtf3, data);
        QtCSV::Writer::write(csv_filepath, data);
        break;
    case 1:
        wtf.exec((m_contasks->query().executedQuery()));
        fillData(wtf, wtf3, data);
        QtCSV::Writer::write(csv_filepath, data);
        break;
    case 2:
        wtf.exec((m_custasks->query().executedQuery()));
        fillData(wtf, wtf3, data);
        QtCSV::Writer::write(csv_filepath, data);
        break;
    }
}