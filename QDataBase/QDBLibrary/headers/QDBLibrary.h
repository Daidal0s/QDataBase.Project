#pragma once
#include <orm/db.hpp>

using Orm::DB;

auto manager = DB::create({
    {"mysql", {
    {"driver",          "QMYSQL"},
    {"host",            qEnvironmentVariable("DB_HOST", "127.0.0.1")},
    {"port",            qEnvironmentVariable("DB_PORT", "3306")},
    {"database",        qEnvironmentVariable("DB_DATABASE", "QDB")},
    {"username",        qEnvironmentVariable("DB_USERNAME", "qdb")},
    {"password",        qEnvironmentVariable("DB_PASSWORD", "t3ngentoppagur3nlag4nn")},
    {"charset",         qEnvironmentVariable("DB_CHARSET", "utf8mb4")},
    {"collation",       qEnvironmentVariable("DB_COLLATION", "utf8mb4_unicode_520_ci")},
    {"timezone",        "+00:00"},
    {"qt_timezone",     QVariant::fromValue(Qt::LocalTime)},
    {"prefix",          ""},
    {"prefix_indexes",  false},
    {"strict",          true},
    {"engine",          "InnoDB"},
    {"options",         QVariantHash()},
    }},
});