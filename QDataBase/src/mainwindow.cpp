#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dev.h"


void setupModel(QSharedPointer<QSqlRelationalTableModel> &model, const QString &nameOfTable)
{
    if (Orm::Schema::hasTable(nameOfTable))
    {
        model->setTable(nameOfTable);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setJoinMode(QSqlRelationalTableModel::InnerJoin);
    }
}

void setTablesNames(QStringList &list)
{
    auto tableNamesDB = Orm::Schema::getAllTables();

    while(tableNamesDB.next())
    {
#ifdef DEV_BUILD
        list.push_back(tableNamesDB.value("Tables_in_Test").toString());
#else
        list.push_back(tableNamesDB.value("Tables_in_QDB").toString());
#endif
    }
}

void fillRelationalTable(QVector<QSharedPointer<QSqlRelationalTableModel>> &tableWithModels, const QList<QString> &tableWithNames)
{
    for (const auto &c : tableWithNames)
    {
        tableWithModels.push_back(QSharedPointer<QSqlRelationalTableModel>(new QSqlRelationalTableModel()));
        setupModel(tableWithModels.last(), c);
        tableWithModels.last()->select();

        qDebug() << tableWithModels.last()->tableName() << " FILLED!";
    }
}

void MainWindow::clearHidden(const QSqlRelationalTableModel *model)
{
    for(int iii = 0; iii < model->columnCount(); ++iii)
    {
        if (ui->tv_sql->isColumnHidden(iii))
            ui->tv_sql->showColumn(iii);
    }
}

void MainWindow::setTablesAndFillables()
{
    int index = 0;

    for (const auto c : _tableNamesList)
    {
        _tablesAndFillables[c] = QStringList();
        _tableNames[c] = index++;
    }

    for (auto c : _tableNames)
    {
        switch (c)
        {
        case 0:
            _tablesAndFillables["consumers_tasks"] = ConsumerTask::getFillableList();
            break;
        case 1:
            _tablesAndFillables["customers_tasks"] = CustomersTask::getFillableList();
            break;
        case 2:
            _tablesAndFillables["employee_positions"] = EmployeePosition::getFillableList();
            break;
        case 3:
            _tablesAndFillables["employee_status"] = EmployeeStatus::getFillableList();
            break;
        case 4:
            _tablesAndFillables["employees"] = Employee::getFillableList();
            break;
        case 5:
            _tablesAndFillables["legal_forms"] = LegalForm::getFillableList();
            break;
        case 6:
            _tablesAndFillables["project_status"] = ProjectStatus::getFillableList();
            break;
        case 7:
            _tablesAndFillables["projects"] = Project::getFillableList();
            break;
        case 8:
            _tablesAndFillables["projects_employees"] = ProjectRelatedEmployees::getFillableList();
            break;
        case 9:
            _tablesAndFillables["roles"] = Role::getFillableList();
            break;
        case 10:
            _tablesAndFillables["task_status_consumer"] = TaskStatusConsumer::getFillableList();
            break;
        case 11:
            _tablesAndFillables["task_status_customer"] = TaskStatusCustomer::getFillableList();
            break;
        case 12:
            _tablesAndFillables["task_type_consumer"] = TaskTypeConsumer::getFillableList();
            break;
        case 13:
            _tablesAndFillables["task_type_customer"] = TaskTypeCustomer::getFillableList();
            break;
        case 14:
            _tablesAndFillables["user_data"] = ProjectStatus::getFillableList();
            break;
        default:
            break;
        }
    }
}

void MainWindow::setFillFields(const QSqlRelationalTableModel *model)
{
    _namesForFill.clear();

    _namesForFill = _tablesAndFillables[model->tableName()];

    for (int iii = 0; iii < _namesForFill.size(); ++iii)
    {
        _fillableFields.push_back(QSharedPointer<QTextEdit>(new QTextEdit()));
        _fillableFields.last()->setPlaceholderText(_namesForFill.at(iii));
    }
}

void MainWindow::printFillableFields()
{
    for (auto c : _fillableFields)
    {
        ui->vl_fillableFields->addWidget(c.get());
    }
}

MainWindow::MainWindow(Login::ROLE userRole, QMainWindow *parent)
    : _userRole(userRole), QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTablesNames(_tableNamesList);
    fillRelationalTable(_modelVector, _tableNamesList);
    setTablesAndFillables();
    ui->cb_model->addItems(_tableNamesList);
    
    this->hide();

    if (dbConnection.getDB().isOpen())
    {
        this->show();
        ui->tv_sql->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tv_sql->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tv_sql->setItemDelegate(new QSqlRelationalDelegate(ui->tv_sql));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cb_model_currentIndexChanged(int index)
{
    auto model = _modelVector.at(index).get();
    clearHidden(model);

    ui->tv_sql->setModel(model);

    ui->tv_sql->resizeColumnsToContents();

    setFillFields(model);
    printFillableFields();
}

void MainWindow::on_pb_submitChanges_clicked()
{
    _modelVector.at(ui->cb_model->currentIndex())->submitAll();
}

void MainWindow::on_actionTo_csv_triggered()
{
    QString csv_filepath = QDir::currentPath() + "/export.csv";

    QtCSV::StringData csvData;
    auto query = DB::qtQuery();
    QList<QList<QString>> excelModel;

    auto fillData = 
    [] (QSqlQuery &query, QList<QList<QString>> &excelModel, QtCSV::StringData &csvData)
    {
        QList<QString> rowOfTable;

        while (query.next())
        {
            for (int iii = 1;iii <= 8;++iii)
            {
                rowOfTable.push_back(query.value(iii).toString());
            }
            excelModel.push_back(rowOfTable);
            rowOfTable.clear();
        }

        for(int iii = 0; iii < excelModel.size(); ++iii)
        {
            csvData.addRow(excelModel.at(iii));
        }
    };

    query.exec((_modelVector.at(ui->cb_model->currentIndex())->query().executedQuery()));
    fillData(query, excelModel, csvData);
    QtCSV::Writer::write(csv_filepath, csvData);
}