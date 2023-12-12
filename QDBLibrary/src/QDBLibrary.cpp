#include "QDBLibrary.h"

using Orm::Schema;

void createDB()
{
    int countOfCreatedTables = 0;

    if (!Schema::hasTable("roles"))
    {
        Schema::create("roles", [](Orm::SchemaNs::Blueprint &table)
        {
           table.increments("id");
           table.string("RoleName").nullable();
           table.tinyText("Description").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("employee_positions"))
    {
        Schema::create("employee_positions", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("PositionName").nullable();
            table.tinyText("Description").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("employee_status"))
    {
        Schema::create("employee_status", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("EmployeeStatus").nullable();
            table.tinyText("Description").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("legal_forms"))
    {
        Schema::create("legal_forms", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("LegalFormName").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("project_status"))
    {
        Schema::create("project_status", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("ProjectStatusName").nullable();
            table.tinyText("Description").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("task_type_customer"))
    {
        Schema::create("task_type_customer", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("TaskType").nullable();
            table.tinyText("Description").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("task_status_customer"))
    {
        Schema::create("task_status_customer", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("TaskStatus").nullable();
            table.tinyText("Description").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("task_type_consumer"))
    {
        Schema::create("task_type_consumer", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("TaskType").nullable();
            table.tinyText("Description").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("task_status_consumer"))
    {
        Schema::create("task_status_consumer", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("TaskStatus").nullable();
            table.tinyText("Description").nullable(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("user_data"))
    {
        Schema::create("user_data", [](Orm::SchemaNs::Blueprint &table)
        {
            table.string("Login").primary();
            table.string("Password").nullable();
            table.unsignedInteger("RoleID").nullable();

            table.foreign("RoleID").references("id").on("roles").nullOnDelete().cascadeOnUpdate(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("employees"))
    {
        Schema::create("employees", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("AuthData").nullable();
            table.string("FIO").nullable();
            table.string("PassportData").nullable();
            table.date("BirthDay").nullable();
            table.unsignedInteger("PositionID").nullable();
            table.string("ContactDataNum").nullable();
            table.string("ContactDataEMail").nullable();
            table.unsignedInteger("StatusID").nullable();
            table.unsignedInteger("ComplitedTasks").nullable();

            table.foreign("AuthData").references("Login").on("user_data").cascadeOnDelete().cascadeOnUpdate();
            table.foreign("PositionID").references("id").on("employee_positions").nullOnDelete().cascadeOnUpdate();
            table.foreign("StatusID").references("id").on("employee_status").nullOnDelete().cascadeOnUpdate(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("consumers_tasks"))
    {
        Schema::create("consumers_tasks", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("TaskID");
            table.string("FIO").nullable();
            table.unsignedInteger("TaskTypeID").nullable();
            table.string("ContactDataNum").nullable();
            table.string("RelatedEmployee").nullable();
            table.unsignedInteger("StatusID").nullable();
            table.timestamps();
            
            table.foreign("TaskTypeID").references("id").on("task_type_consumer").nullOnDelete().cascadeOnUpdate();
            table.foreign("RelatedEmployee").references("Login").on("user_data").nullOnDelete().cascadeOnUpdate();
            table.foreign("StatusID").references("id").on("task_status_consumer").nullOnDelete().cascadeOnUpdate(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("projects"))
    {
        Schema::create("projects", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("ProjectID");
            table.string("ProjectName").nullable();
            table.string("TeamLeader").nullable();
            table.text("Description").nullable();
            table.text("Documentation").nullable();
            table.unsignedInteger("StatusID").nullable();
            table.timestamps();
            
            table.foreign("TeamLeader").references("Login").on("user_data").nullOnDelete().cascadeOnUpdate();
            table.foreign("StatusID").references("id").on("project_status").nullOnDelete().cascadeOnUpdate(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("projects_employees"))
    {
        Schema::create("projects_employees", [](Orm::SchemaNs::Blueprint &table)
        {
            table.unsignedInteger("ProjectID");
            table.string("Employee");

            table.foreign("ProjectID").references("ProjectID").on("projects").restrictOnDelete().cascadeOnUpdate();
            table.foreign("Employee").references("Login").on("user_data").restrictOnDelete().cascadeOnUpdate(); 
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("customers_tasks"))
    {
        Schema::create("customers_tasks", [](Orm::SchemaNs::Blueprint &table)
        {
            table.string("INN").primary();
            table.unsignedInteger("LegalFormID").nullable();
            table.string("Name").nullable();
            table.tinyText("Adress").nullable();
            table.unsignedInteger("TaskTypeID").nullable();
            table.unsignedInteger("Profitability").nullable();
            table.string("ContactDataNum").nullable();
            table.unsignedInteger("StatusID").nullable();
            table.unsignedInteger("RelatedProject").nullable();
            table.timestamps();
            
            table.foreign("LegalFormID").references("id").on("legal_forms").nullOnDelete().cascadeOnUpdate();
            table.foreign("TaskTypeID").references("id").on("task_type_customer").nullOnDelete().cascadeOnUpdate();
            table.foreign("StatusID").references("id").on("task_status_customer").nullOnDelete().cascadeOnUpdate();
            table.foreign("RelatedProject").references("ProjectID").on("projects").nullOnDelete().cascadeOnUpdate(); 
        });

        ++countOfCreatedTables;
    }

    qDebug() << "Count of new created tabels: " << countOfCreatedTables;
}

void testModels()
{
    Role::updateOrCreate({{"RoleName", "AAAA"}, {"Description", "AAAAA"}});

    auto ep = EmployeePosition::updateOrCreate({});

    auto es = EmployeeStatus::updateOrCreate({});

    auto lf = LegalForm::updateOrCreate({});

    auto ps = ProjectStatus::updateOrCreate({});

    auto tsco = TaskStatusConsumer::updateOrCreate({});

    auto tscu = TaskStatusCustomer::updateOrCreate({});

    auto ttco = TaskTypeConsumer::updateOrCreate({});

    auto ttcu = TaskTypeCustomer::updateOrCreate({});

    auto ud = UserData::create(
        {
            {"Login", "aaAaa"},
            {"Password", "aafAaa"},
            {"RoleID", 1},
        });

    auto e = Employee::create(
        {
            {"AuthData", "aaAaa"},
            {"FIO", "ooOOoooO"},
            {"PassportData", "ooOOoooO"},
            {"BirthDay", QDate::currentDate()},
            {"PositionID", 1},
            {"ContactDataNum", "ooOOoooO"},
            {"ContactDataEMail", "ooOOoooO"},
            {"StatusID", 1},
        });

    auto cot = ConsumerTask::updateOrCreate(
        {
            {"FIO", "asfsdlkfgjnd"},
            {"TaskTypeID", 1},
            {"ContactDataNum", "asdas"},
            {"RelatedEmployee", "aaAaa"},
            {"StatusID", 1},
        });

    auto p = Project::updateOrCreate(
        {
            {"ProjectName", "loi"},
            {"TeamLeader", "aaAaa"},
            {"Description", "loi"},
            {"Documentation", "loi"},
            {"StatusID", 1},
        });

    auto cut = CustomersTask::create(
        {
            {"INN", "fgksl"},
            {"LegalFormID", 1},
            {"Name", "fgkl"},
            {"Adress", "fgkl"},
            {"TaskTypeID", 1},
            {"Profitability", 9999},
            {"ContactDataNum", "ffgkl"},
            {"StatusID", 1},
            {"RelatedProject", 1},
        });

    auto pre = ProjectRelatedEmployees::create(
        {
            {"ProjectID", 1},
            {"Employee", "aaAaa"},
        });

    pre.whereEq("ProjectID", 1)->remove();
    cut.whereEq("INN", "fgksl")->remove();
    p.remove();
    cot.remove();
    e.whereEq("AuthData", "aaAaa")->remove();
    ud.whereEq("Login", "aaAaa")->remove();
    ttcu.remove();
    ttco.remove();
    tscu.remove();
    tsco.remove();
    ps.remove();
    lf.remove();
    es.remove();
    ep.remove();
    Role::where("id", "!=", "0")->remove();

    qDebug() << "Test complited!";
}

void fillDB(bool isCreatedBefore)
{
    if (UserData::whereEq("Login", "maycraftHolms4ever")->exists())
    {
        qDebug() << "Database already exists";
        return;
    }

    Role::updateOrCreate(
        {
            {"RoleName", "Админ"},
        });

    Role::updateOrCreate(
        {
            {"RoleName", "Разработчик"},
        });

    Role::updateOrCreate(
        {
            {"RoleName", "Тимлидер"},
        });

    EmployeePosition::updateOrCreate(
        {
            {"PositionName", "Администратор"},
            {"Description", "Сопровождает систему"},
        });

    EmployeePosition::updateOrCreate(
        {
            {"PositionName", "Разработчик"},
            {"Description", "Создаёт программы, решает задачи от пользователей"},
        });

    EmployeePosition::updateOrCreate(
        {
            {"PositionName", "Тимлидер"},
            {"Description", "Руководит проектами, выдаёт задания разработчикам"},
        });

    EmployeeStatus::updateOrCreate(
        {
            {"EmployeeStatus", "Стажируется"},
            {"Description", ""},
        });

    EmployeeStatus::updateOrCreate(
        {
            {"EmployeeStatus", "Работает"},
            {"Description", ""},
        });

    EmployeeStatus::updateOrCreate(
        {
            {"EmployeeStatus", "На больничном"},
            {"Description", ""},
        });

    EmployeeStatus::updateOrCreate(
        {
            {"EmployeeStatus", "В отпуске"},
            {"Description", ""},
        });

    EmployeeStatus::updateOrCreate(
        {
            {"EmployeeStatus", "Уволен"},
            {"Description", ""},
        });

    LegalForm::updateOrCreate(
        {
            {"LegalFormName", "ООО"},
        });

    LegalForm::updateOrCreate(
        {
            {"LegalFormName", "АО"},
        });

    LegalForm::updateOrCreate(
        {
            {"LegalFormName", "ИП"},
        });

    ProjectStatus::updateOrCreate(
        {
            {"ProjectStatusName", "На рассмотрении"},
            {"Description", ""},
        });

    ProjectStatus::updateOrCreate(
        {
            {"ProjectStatusName", "Заморожен"},
            {"Description", ""},
        });

    ProjectStatus::updateOrCreate(
        {
            {"ProjectStatusName", "В разработке"},
            {"Description", ""},
        });

    ProjectStatus::updateOrCreate(
        {
            {"ProjectStatusName", "Сопровождается"},
            {"Description", ""},
        });

    ProjectStatus::updateOrCreate(
        {
            {"ProjectStatusName", "Закрыт"},
            {"Description", ""},
        });

    TaskStatusConsumer::updateOrCreate(
        {
            {"TaskStatus", "В обработке"},
            {"Description", ""},
        });

    TaskStatusConsumer::updateOrCreate(
        {
            {"TaskStatus", "В процессе решения"},
            {"Description", ""},
        });

    TaskStatusConsumer::updateOrCreate(
        {
            {"TaskStatus", "Проблема решена"},
            {"Description", ""},
        });

    TaskStatusCustomer::updateOrCreate(
        {{"TaskStatus", "На рассмотрении"},
         {"Description", ""}});

    TaskStatusCustomer::updateOrCreate(
        {{"TaskStatus", "Отклонено"},
         {"Description", ""}});

    TaskStatusCustomer::updateOrCreate(
        {{"TaskStatus", "В разработке"},
         {"Description", ""}});

    TaskStatusCustomer::updateOrCreate(
        {{"TaskStatus", "Сопровождается"},
         {"Description", ""}});

    TaskStatusCustomer::updateOrCreate(
        {{"TaskStatus", "Закончено"},
         {"Description", ""}});

    TaskTypeCustomer::updateOrCreate(
        {
            {"TaskType", "Разработка"},
            {"Description", ""},
        });

    TaskTypeCustomer::updateOrCreate(
        {
            {"TaskType", "Помощь в разработке"},
            {"Description", ""},
        });

    TaskTypeCustomer::updateOrCreate(
        {
            {"TaskType", "Помощь в сопровождении"},
            {"Description", ""},
        });

    TaskTypeConsumer::updateOrCreate(
        {
            {"TaskType", "Проблема во время работы"},
            {"Description", ""},
        });

    TaskTypeConsumer::updateOrCreate(
        {
            {"TaskType", "Проблема с запуском"},
            {"Description", ""},
        });

    if (isCreatedBefore)
    {
        UserData::create(
            {
                {"Login", "admin"},
                {"Password", "admin"},
                {"RoleID", 1},
            });

        UserData::create(
            {
                {"Login", "kitaec2312"},
                {"Password", "fopkldfjgh"},
                {"RoleID", 2},
            });

        UserData::create(
            {
                {"Login", "microchelik2004"},
                {"Password", "adskiypes12"},
                {"RoleID", 2},
            });

        UserData::create(
            {
                {"Login", "tsarbatushka666"},
                {"Password", "iamg0d"},
                {"RoleID", 3},
            });

        Employee::create(
            {
                {"AuthData", "admin"},
                {"FIO", "admin"},
                {"PassportData", "no matter"},
                {"BirthDay", QDate::currentDate()},
                {"PositionID", 1},
                {"ContactDataNum", "on the moon"},
                {"ContactDataEMail", "mkjnhud@gmail.com"},
                {"StatusID", 3},
                {"ComplitedTasks",0},
            });

        Employee::create(
            {
                {"AuthData", "kitaec2312"},
                {"FIO", "Захурат Бишбадан Дусынтенбекович"},
                {"PassportData", "Китайский номер, на иероглифах не понятно"},
                {"BirthDay", QDate::currentDate()},
                {"PositionID", 2},
                {"ContactDataNum", "+7 909 678 14 65"},
                {"ContactDataEMail", "iamrasist2@gmail.com"},
                {"StatusID", 2},
                {"ComplitedTasks",5},
            });

        Employee::create(
            {
                {"AuthData", "microchelik2004"},
                {"FIO", "Зеленовский Владимир Андреев"},
                {"PassportData", "25 86 800496"},
                {"BirthDay", QDate::currentDate()},
                {"PositionID", 2},
                {"ContactDataNum", "+7 865 678 54 67"},
                {"ContactDataEMail", "cripper.minecraft@gmail.com"},
                {"StatusID", 1},
                {"ComplitedTasks",5},
            });

        Employee::create(
            {
                {"AuthData", "tsarbatushka666"},
                {"FIO", "Златогоров Иерахим Сулийский"},
                {"PassportData", "Паспорт древнего Рима"},
                {"BirthDay", QDate::currentDate()},
                {"PositionID", 3},
                {"ContactDataNum", "Помолись"},
                {"ContactDataEMail", "theEmperor@emperium.com"},
                {"StatusID", 2},
                {"ComplitedTasks",8},
            });
    }

    UserData::create(
    {
        {"Login", "vadik024"},
        {"Password", "genius"},
        {"RoleID", 2},
    });

    UserData::create(
    {
        {"Login", "volonDeMort"},
        {"Password", "DumbledoreIsDeadIsNice"},
        {"RoleID", 2},
    });

    UserData::create(
    {
        {"Login", "dmitroUK"},
        {"Password", "noUnitedKingdom21"},
        {"RoleID", 2},
    });

    UserData::create(
    {
        {"Login", "maycraftHolms4ever"},
        {"Password", "lilSherlokStupid"},
        {"RoleID", 2},
    });

    Employee::create(
    {
        {"AuthData", "vadik024"},
        {"FIO", "Ставропольский Владислав Валерьевич"},
        {"PassportData", "87 89 766852"},
        {"BirthDay", QDate::currentDate()},
        {"PositionID", 2},
        {"ContactDataNum", "+7 967 234 32 00"},
        {"ContactDataEMail", "iramonami@gmail.com"},
        {"StatusID", 2},
        {"ComplitedTasks",7},
    });

    Employee::create(
    {
        {"AuthData", "volonDeMort"},
        {"FIO", "Воланд Андрей Иисаков"},
        {"PassportData", "12 67 876510"},
        {"BirthDay", QDate::currentDate()},
        {"PositionID", 2},
        {"ContactDataNum", "+7 967 234 32 00"},
        {"ContactDataEMail", "iramonami@gmail.com"},
        {"StatusID", 2},
        {"ComplitedTasks",12},
    });

    Employee::create(
    {
        {"AuthData", "dmitroUK"},
        {"FIO", "Исако Дмитро Миколович"},
        {"PassportData", "87 89 997895"},
        {"BirthDay", QDate::currentDate()},
        {"PositionID", 2},
        {"ContactDataNum", "+7 952 332 32 00"},
        {"ContactDataEMail", "ferariUK@gmail.com"},
        {"StatusID", 2},
        {"ComplitedTasks",1},
    });

    Employee::create(
    {
        {"AuthData", "maycraftHolms4ever"},
        {"FIO", "Холмс Мэйкрафт Иванович"},
        {"PassportData", "87 89 682006"},
        {"BirthDay", QDate::currentDate()},
        {"PositionID", 2},
        {"ContactDataNum", "+7 972 916 32 00"},
        {"ContactDataEMail", "holmses4ever@gmail.com"},
        {"StatusID", 2},
        {"ComplitedTasks",22},
    });

    ConsumerTask::updateOrCreate(
        {
            {"FIO", "Язагит Лера"},
            {"TaskTypeID", 1},
            {"ContactDataNum", "Placeholder"},
            {"RelatedEmployee", "microchelik2004"},
            {"StatusID", 2},
        });

    ConsumerTask::updateOrCreate(
        {
            {"FIO", "Иван Капустин"},
            {"TaskTypeID", 2},
            {"ContactDataNum", "Placeholder"},
            {"RelatedEmployee", "microchelik2004"},
            {"StatusID", 2},
        });

    ConsumerTask::updateOrCreate(
    {
        {"FIO", "Чёрный Сталкер"},
        {"TaskTypeID", 2},
        {"ContactDataNum", "Placeholder"},
        {"RelatedEmployee", "kitaec2312"},
        {"StatusID", 3},
    });

    ConsumerTask::updateOrCreate(
    {
        {"FIO", "Белый Сталкер"},
        {"TaskTypeID", 1},
        {"ContactDataNum", "Placeholder"},
        {"RelatedEmployee", "vadik024"},
        {"StatusID", 2},
    });
    
    ConsumerTask::updateOrCreate(
    {
        {"FIO", "Гендальф Серый"},
        {"TaskTypeID", 2},
        {"ContactDataNum", "Placeholder"},
        {"RelatedEmployee", "volonDeMort"},
        {"StatusID", 1},
    });

    ConsumerTask::updateOrCreate(
    {
        {"FIO", "Военкомат"},
        {"TaskTypeID", 2},
        {"ContactDataNum", "Placeholder"},
        {"RelatedEmployee", "dmitroUK"},
        {"StatusID", 2},
    });

    ConsumerTask::updateOrCreate(
    {
        {"FIO", "Шерлок Холмс"},
        {"TaskTypeID", 2},
        {"ContactDataNum", "Placeholder"},
        {"RelatedEmployee", "maycraftHolms4ever"},
        {"StatusID", 3},
    });

    Project::updateOrCreate(
        {
            {"ProjectName", "Big Project 2007"},
            {"TeamLeader", "tsarbatushka666"},
            {"Description", ""},
            {"Documentation", ""},
            {"StatusID", 3},
        });

    if (isCreatedBefore)
    {
        CustomersTask::create(
            {
                {"INN", "684654653564531253564"},
                {"LegalFormID", 2},
                {"Name", "КасПром"},
                {"Adress", "Ул. 60 лет Крсаному террору, город Боголюбенск"},
                {"TaskTypeID", 1},
                {"Profitability", 999998899},
                {"ContactDataNum", "+7 345 800 24 50"},
                {"StatusID", 1},
                {"RelatedProject", 1},
            });

        ProjectRelatedEmployees::create(
            {
                {"ProjectID", 1},
                {"Employee", "kitaec2312"},
            });

        ProjectRelatedEmployees::create(
            {
                {"ProjectID", 1},
                {"Employee", "microchelik2004"},
            });

        ProjectRelatedEmployees::create(
            {
                {"ProjectID", 1},
                {"Employee", "tsarbatushka666"},
            });
    }

    ProjectRelatedEmployees::create(
    {
        {"ProjectID", 1},
        {"Employee", "vadik024"},
    });

    ProjectRelatedEmployees::create(
    {
        {"ProjectID", 1},
        {"Employee", "volonDeMort"},
    });

    ProjectRelatedEmployees::create(
    {
        {"ProjectID", 1},
        {"Employee", "dmitroUK"},
    });

    ProjectRelatedEmployees::create(
    {
        {"ProjectID", 1},
        {"Employee", "maycraftHolms4ever"},
    });
    
}