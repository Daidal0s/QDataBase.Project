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
           table.string("RoleName");
           table.tinyText("Description").nullable();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("employee_positions"))
    {
        Schema::create("employee_positions", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("PositionName");
            table.tinyText("Description").nullable();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("employee_status"))
    {
        Schema::create("employee_status", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("EmployeeStatus");
            table.tinyText("Description").nullable();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("legal_forms"))
    {
        Schema::create("legal_forms", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("LegalFormName");
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("project_status"))
    {
        Schema::create("project_status", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("ProjectStatusName");
            table.tinyText("Description").nullable();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("task_type_customer"))
    {
        Schema::create("task_type_customer", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("TaskType");
            table.tinyText("Description").nullable();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("task_status_customer"))
    {
        Schema::create("task_status_customer", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("TaskStatus");
            table.tinyText("Description").nullable();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("task_type_consumer"))
    {
        Schema::create("task_type_consumer", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("TaskType");
            table.tinyText("Description").nullable();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("task_status_consumer"))
    {
        Schema::create("task_status_consumer", [](Orm::SchemaNs::Blueprint &table)
        {
            table.increments("id");
            table.string("TaskStatus");
            table.tinyText("Description").nullable();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("user_data"))
    {
        Schema::create("user_data", [](Orm::SchemaNs::Blueprint &table)
        {
            table.string("Login").primary();
            table.string("Password");
            table.unsignedInteger("RoleID").nullable();

            table.foreign("RoleID").references("id").on("roles").nullOnDelete().cascadeOnUpdate();
        });

        ++countOfCreatedTables;
    }

    if (!Schema::hasTable("employees"))
    {
        Schema::create("employees", [](Orm::SchemaNs::Blueprint &table)
        {
            table.string("AuthData");
            table.string("FIO");
            table.string("PassportData");
            table.date("BirthDay");
            table.unsignedInteger("PositionID").nullable();
            table.string("ContactDataNum").nullable();
            table.string("ContactDataEMail").nullable();
            table.unsignedInteger("StatusID").nullable();
            
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
            table.string("FIO");
            table.unsignedInteger("TaskTypeID").nullable();
            table.string("ContactDataNum");
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
            table.string("ProjectName");
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
            table.string("Name");
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
        }
    );

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
        }
    );

    auto cot = ConsumerTask::updateOrCreate(
        {
            {"FIO", "asfsdlkfgjnd"},
            {"TaskTypeID", 1},
            {"ContactDataNum", "asdas"},
            {"RelatedEmployee", "aaAaa"},
            {"StatusID", 1},
        }
    );

    auto p = Project::updateOrCreate(
        {
            {"ProjectName", "loi"},
            {"TeamLeader", "aaAaa"},
            {"Description", "loi"},
            {"Documentation", "loi"},
            {"StatusID", 1},
        }
    );

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
        }
    );

    auto pre = ProjectRelatedEmployees::create(
        {
            {"ProjectID", 1},
            {"Employee", "aaAaa"},
        }
    );

    pre.whereEq("ProjectID", 1)->remove();
    cut.whereEq("INN","fgksl")->remove();
    p.remove();
    cot.remove();
    e.whereEq("AuthData","aaAaa")->remove();
    ud.whereEq("Login","aaAaa")->remove();
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