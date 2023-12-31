#pragma once
#include "stdafx.h"
#include "AllModels.h"

using Orm::DB;

inline std::shared_ptr<Orm::DatabaseManager> manager = DB::create({
    {"mysql", {
    {"driver",          "QMYSQL"},
    {"host",            qEnvironmentVariable("DB_HOST", "127.0.0.1")},
    {"port",            qEnvironmentVariable("DB_PORT", "3306")},
#ifdef DEV_BUILD
    {"database",        qEnvironmentVariable("DB_DATABASE", "Test")},
#else
    {"database",        qEnvironmentVariable("DB_DATABASE", "QDB")},
#endif
    {"username",        qEnvironmentVariable("DB_USERNAME", "qdb")},
    {"password",        qEnvironmentVariable("DB_PASSWORD", "t3ngentoppagur3nlag4nn")},
    {"charset",         qEnvironmentVariable("DB_CHARSET", "utf8mb4")},
    {"collation",       qEnvironmentVariable("DB_COLLATION", "utf8mb4_unicode_520_ci")},
    {"timezone",        "+05:00"},
    {"qt_timezone",     QVariant::fromValue(Qt::LocalTime)},
    {"prefix",          ""},
    {"prefix_indexes",  false},
    {"strict",          true},
    {"engine",          "InnoDB"},
    {"options",         Orm::Utils::Configuration::mysqlSslOptions()},
    }},
}, "mysql");

void createDB();

void testModels();

void fillDB(bool isCreatedBefore);