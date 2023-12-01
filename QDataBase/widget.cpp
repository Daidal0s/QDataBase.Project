#include "widget.h"
#include "ui_widget.h"

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
    auto qdb = QSqlDatabase::addDatabase("QMYSQL");
    qdb.setHostName("127.0.0.1");
    qdb.setPort(3306);
    qdb.setUserName("qdb");
    qdb.setPassword("t3ngentoppagur3nlag4nn");
    qdb.setDatabaseName("QDB");

    qdb.open();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *layout = new QHBoxLayout();

    QPushButton *btn = new QPushButton();
    btn->setText("CreateDB");
    connect(btn, SIGNAL(clicked()), SLOT(DEV_createDB()));

    QPushButton *btn2 = new QPushButton();
    btn2->setText("TestBD");
    connect(btn2, SIGNAL(clicked()), SLOT(DEV_testBD()));

    QPushButton *btn3 = new QPushButton();
    btn3->setText("Fill Role, Position, Auth, Status, Employee");
    connect(btn3, SIGNAL(clicked()), SLOT(DEV_fillSomeTables()));

    QPushButton *btn4 = new QPushButton();
    btn4->setText("Fill BD");
    connect(btn4, SIGNAL(clicked()), SLOT(DEV_fillAllTables()));

    layout->addWidget(btn);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);

    // auto names = Employee::value("Login").toList();
    // auto empp = Employee::findMany(names);
    
    qDebug() << Project::all().size() << " " << Project::first()->toVector().toList().size();

    mainLayout->addLayout(layout);

    if (qdb.isOpen())
    {
        auto tablem = new QSqlRelationalTableModel();
        tablem->setRelation(7, QSqlRelation("employee_status","id","EmployeeStatus"));
        tablem->setTable("employees");
        tablem->select();
        // tablem->setQuery(empp);

        auto table = new QTableView();
        table->setModel(testTable);
        mainLayout->addWidget(table);
    }
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

void Widget::DEV_fillSomeTables()
{
    if (UserData::count() == 0)
    {
        auto role = Role::firstOrCreate(
            {
                {"RoleName", "User"},
            });

        auto auth = UserData::create(
            {
                {"Login", "pivo2323"},
                {"Password", "dochkaSuper"},
                {"RoleID", 1},
            });

        auto eplPos = EmployeePosition::firstOrCreate(
            {
                {"PositionName", "Genius"},
            });

        auto eplStatus = EmployeeStatus::firstOrCreate(
            {
                {"EmployeeStatus", "Alive"},
            });

        auto epl = Employee::create(
            {
                {"AuthData", "pivo2323"},
                {"FIO", "Zubenko Кирил Mefody"},
                {"PassportData", "22 81 337228"},
                {"BirthDay", QDate::currentDate()},
                {"PositionID", "1"},
                {"ContactDataNum", "+7 777 777 77 77"},
                {"ContactDataEMail", "mama@mama.su"},
                {"StatusID", "1"},
            });
    }

    Employee::all().toVector();
}

void Widget::DEV_fillAllTables()
{
    fillDB(true);
}
