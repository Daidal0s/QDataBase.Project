#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dev.h"


QStringList MainWindow::getRemoveColumn() const
{
    QVariantList variantsToStrings;
    QStringList names;
    switch (_tableNames[_currentModel->tableName()])
    {
    case 0:
        variantsToStrings = ConsumerTask::pluck("TaskID").toList();
        break;
    case 1:
        variantsToStrings = CustomersTask::pluck("INN").toList();
        break;
    case 2:
        variantsToStrings = EmployeePosition::pluck("id").toList();
        break;
    case 3:
        variantsToStrings = EmployeeStatus::pluck("id").toList();
        break;
    case 4:
        variantsToStrings = Employee::pluck("AuthData").toList();
        break;
    case 5:
        variantsToStrings = LegalForm::pluck("id").toList();
        break;
    case 6:
        variantsToStrings = ProjectStatus::pluck("id").toList();
        break;
    case 7:
        variantsToStrings = Project::pluck("ProjectName").toList();
        break;
    case 8:
        variantsToStrings.push_back("Nothing To Delete");
        break;
    case 9:
        variantsToStrings = Role::pluck("id").toList();
        break;
    case 10:
        variantsToStrings = TaskStatusConsumer::pluck("id").toList();
        break;
    case 11:
        variantsToStrings = TaskStatusCustomer::pluck("id").toList();
        break;
    case 12:
        variantsToStrings = TaskTypeConsumer::pluck("id").toList();
        break;
    case 13:
        variantsToStrings = TaskTypeCustomer::pluck("id").toList();
        break;
    case 14:
        variantsToStrings = UserData::pluck("Login").toList();
        break;
    default:
        break;
    }

    for (auto c : variantsToStrings)
    {
        names.push_back(c.toString());
    }

    return names;
}

void setupModel(QSharedPointer<QSqlRelationalTableModel> &model, const QString &nameOfTable)
{
    if (Orm::Schema::hasTable(nameOfTable))
    {
        model->setTable(nameOfTable);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setJoinMode(QSqlRelationalTableModel::InnerJoin);
    }
}

QMap<QString, int> fillEmployeeMap()
{
    auto map = QMap<QString, int>();
    auto employeeNames = Employee::pluck("FIO").toList();

    for (auto c : employeeNames)
    {
        map[c.toString()] = Employee::select("ComplitedTasks")->whereEq("FIO", c.toString()).value("ComplitedTasks").toInt();
    }

    return map;
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

QStringList fillRelationalTable(QVector<QSharedPointer<QSqlRelationalTableModel>> &tableWithModels, const QList<QString> &tableWithNames, const QList<QString> &tableWithFilterNames)
{

    QStringList filteredTableNames = tableWithNames;

    for (const auto &c : tableWithFilterNames)
    {
        filteredTableNames.removeAt(filteredTableNames.indexOf(c));
    }

    for (const auto &c : filteredTableNames)
    {
        tableWithModels.push_back(QSharedPointer<QSqlRelationalTableModel>(new QSqlRelationalTableModel()));
        setupModel(tableWithModels.last(), c);
        tableWithModels.last()->select();

        qDebug() << tableWithModels.last()->tableName() << " FILLED!";
    }

    return filteredTableNames;
}

void MainWindow::setFilterTableNames()
{
    switch (_userRole)
    {
    case Login::ROLE::ADMIN:
        _tableNamesToFilter.push_back("projects_employees");
        break;
    case Login::ROLE::DEV:
        _tableNamesToFilter.push_back("roles");
        _tableNamesToFilter.push_back("customers_tasks");
        _tableNamesToFilter.push_back("employee_positions");
        _tableNamesToFilter.push_back("employee_status");
        _tableNamesToFilter.push_back("employees");
        _tableNamesToFilter.push_back("legal_forms");
        _tableNamesToFilter.push_back("project_status");
        _tableNamesToFilter.push_back("projects");
        _tableNamesToFilter.push_back("projects_employees");
        _tableNamesToFilter.push_back("task_type_customer");
        _tableNamesToFilter.push_back("task_status_consumer");
        _tableNamesToFilter.push_back("task_status_customer");
        _tableNamesToFilter.push_back("task_type_consumer");
        _tableNamesToFilter.push_back("user_data");
        break;
    case Login::ROLE::TEAMLEADER:
        _tableNamesToFilter.push_back("roles");
        _tableNamesToFilter.push_back("legal_forms");
        _tableNamesToFilter.push_back("employee_status");
        _tableNamesToFilter.push_back("employee_positions");
        _tableNamesToFilter.push_back("project_status");
        _tableNamesToFilter.push_back("task_type_customer");
        _tableNamesToFilter.push_back("task_status_consumer");
        _tableNamesToFilter.push_back("task_status_customer");
        _tableNamesToFilter.push_back("task_type_consumer");
        _tableNamesToFilter.push_back("projects_employees");
        break;
    default:
        break;
    }
}

void MainWindow::clearHidden()
{
    qDebug() << _currentModel->columnCount();

    for(int iii = 0; iii < _currentModel->columnCount(); ++iii)
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
        QStringList();
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
        _fillableFields.last()->setMaximumSize(250,100000);
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


MainWindow::MainWindow(const QString &userName, Login::ROLE userRole, QMainWindow *parent)
    : _userName(userName), _userRole(userRole), QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTablesNames(_tableNamesList);
    setFilterTableNames();
    ui->cb_model->addItems(fillRelationalTable(_modelVector, _tableNamesList, _tableNamesToFilter));
    setTablesAndFillables();

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
    _fillableFields.clear();
    ui->cb_remove->clear();

    _currentModel = QSharedPointer<QSqlRelationalTableModel>(_modelVector.at(index));
    clearHidden();

    ui->cb_remove->addItems(getRemoveColumn());

    ui->tv_sql->setModel(_currentModel.get());

    ui->tv_sql->resizeColumnsToContents();

    setFillFields(_currentModel.get());
    printFillableFields();
}

void MainWindow::on_pb_submitChanges_clicked()
{
    _currentModel->submitAll();
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

void MainWindow::on_pb_createRecord_clicked()
{
    _dataToFill.clear();

    Orm::Tiny::AttributeItem columnAtribute;

    for (int iii = 0; iii < _fillableFields.size(); ++iii)
    {
        columnAtribute.key = _namesForFill.at(iii);
        columnAtribute.value = _fillableFields.at(iii)->toPlainText();
        _dataToFill.push_back(columnAtribute);
    }

    switch (_tableNames[_currentModel->tableName()])
    {
    case 0:
        ConsumerTask::create(_dataToFill);
        break;
    case 1:
        CustomersTask::create(_dataToFill);
        break;
    case 2:
        EmployeePosition::create(_dataToFill);
        break;
    case 3:
        EmployeeStatus::create(_dataToFill);
        break;
    case 4:
        Employee::create(_dataToFill);
        break;
    case 5:
        LegalForm::create(_dataToFill);
        break;
    case 6:
        ProjectStatus::create(_dataToFill);
        break;
    case 7:
        Project::create(_dataToFill);
        break;
    case 8:
        ProjectRelatedEmployees::create(_dataToFill);
        break;
    case 9:
        Role::create(_dataToFill);
        break;
    case 10:
        TaskStatusConsumer::create(_dataToFill);
        break;
    case 11:
        TaskStatusCustomer::create(_dataToFill);
        break;
    case 12:
        TaskTypeConsumer::create(_dataToFill);
        break;
    case 13:
        TaskTypeCustomer::create(_dataToFill);
        break;
    case 14:
        UserData::create(_dataToFill);
        break;
    default:
        break;
    }

    _currentModel->submitAll();

    ui->cb_remove->clear();
    ui->cb_remove->addItems(getRemoveColumn());
}

void MainWindow::on_pb_remove_clicked()
{
    auto rowToRemove = ui->cb_remove->currentText();
    switch (_tableNames[_currentModel->tableName()])
    {
    case 0:
        ConsumerTask::whereEq("TaskID", rowToRemove)->remove();
        break;
    case 1:
        CustomersTask::whereEq("INN", rowToRemove)->remove();
        break;
    case 2:
        EmployeePosition::whereEq("id", rowToRemove)->remove();
        break;
    case 3:
        EmployeeStatus::whereEq("id", rowToRemove)->remove();
        break;
    case 4:
        Employee::whereEq("ProjectName", rowToRemove)->remove();
        break;
    case 5:
        LegalForm::whereEq("", rowToRemove)->remove();
        break;
    case 6:
        ProjectStatus::whereEq("", rowToRemove)->remove();
        break;
    case 7:
        Project::whereEq("", rowToRemove)->remove();
        break;
    case 8:
        break;
    case 9:
        Role::whereEq("id", rowToRemove)->remove();
        break;
    case 10:
        TaskStatusConsumer::whereEq("id", rowToRemove)->remove();
        break;
    case 11:
        TaskStatusCustomer::whereEq("id", rowToRemove)->remove();
        break;
    case 12:
        TaskTypeConsumer::whereEq("id", rowToRemove)->remove();
        break;
    case 13:
        TaskTypeCustomer::whereEq("id", rowToRemove)->remove();
        break;
    case 14:
        UserData::whereEq("Login", rowToRemove)->remove();
        break;
    default:
        break;
    }

    _currentModel->submitAll();

    ui->cb_remove->clear();
    ui->cb_remove->addItems(getRemoveColumn());
}

void MainWindow::on_aData_in_diagrams_triggered()
{
    auto chart = new WorkPie(fillEmployeeMap(), this);
    chart->show();
}

