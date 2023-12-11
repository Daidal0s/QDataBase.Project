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

void getTablesNames(QStringList &list)
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

void MainWindow::fillFields(const QSqlRelationalTableModel *model)
{
    _namesOfFillableFields.clear();

    // switch (model->tableName())
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

    getTablesNames(_tableNames);
    fillRelationalTable(_modelVector, _tableNames);
    ui->cb_model->addItems(_tableNames);
    
    this->hide();

    for (auto c : Role::getFillableList())
    {
        qDebug() << c;
    }

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

    fillFields(model);
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