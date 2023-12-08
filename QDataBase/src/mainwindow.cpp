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
        list.push_back(tableNamesDB.value("Tables_in_QDB").toString());
    }
}

void fillRelationalTable(QVector<QSharedPointer<QSqlRelationalTableModel>> &tableWithModels, const QList<QString> &tableWithNames)
{
    for (const auto &c : tableWithNames)
    {
        tableWithModels.push_back(QSharedPointer<QSqlRelationalTableModel>(new QSqlRelationalTableModel()));
        setupModel(tableWithModels.last(), c);
        tableWithModels.last()->select();
        tableWithModels.last()->query().executedQuery();
        tableWithModels.last()->lastError();

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


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    getTablesNames(tableNames);
    fillRelationalTable(modelVector, tableNames);
    ui->cb_model->addItems(tableNames);
    
#ifdef DEV_BUILD
    w_dev = QSharedPointer<Dev>(new Dev(this));
    w_dev->show();
#endif
    this->hide();

    if (dbConnection.getDB().isOpen())
    {
#ifdef DEV_BUILD
        this->show();
#endif
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
    auto model = modelVector.at(index).get();
    clearHidden(model);

    ui->tv_sql->setModel(model);

    ui->tv_sql->resizeColumnsToContents();

}

void MainWindow::on_pb_submitChanges_clicked()
{
    modelVector.at(ui->cb_model->currentIndex())->submitAll();
}

void MainWindow::on_pb_saveTable_clicked()
{
    QString csv_filepath = QDir::currentPath() + "/export.csv";

    QtCSV::StringData csvData;
    auto query = DB::qtQuery();
    QList<QList<QString>> excelModel;

    auto fillData = 
    [] (QSqlQuery &query, QList<QList<QString>> &excelModel, QtCSV::StringData &csvData)
    {
        QList<QString> wtf2;

        while (query.next())
        {
            for (int iii = 1;iii <= 8;++iii)
            {
                wtf2.push_back(query.value(iii).toString());
            }
            excelModel.push_back(wtf2);
            wtf2.clear();
        }

        for(int iii = 0; iii < excelModel.size(); ++iii)
        {
            csvData.addRow(excelModel.at(iii));
        }
    };

    query.exec((modelVector.at(ui->cb_model->currentIndex())->query().executedQuery()));
    fillData(query, excelModel, csvData);
    QtCSV::Writer::write(csv_filepath, csvData);
}