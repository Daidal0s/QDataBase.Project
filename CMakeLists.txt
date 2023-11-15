cmake_minimum_required(VERSION 3.27)

project(QDataBase VERSION 0.1 LANGUAGES CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

find_package(TinyOrm 0.36.5 CONFIG REQUIRED)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)

add_subdirectory(${CMAKE_SOURCE_DIR}/QDataBase/QDBLibrary)
add_subdirectory(${CMAKE_SOURCE_DIR}/QDataBase)