cmake_minimum_required(VERSION 3.27)

project(QDataBase VERSION 0.1 LANGUAGES CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

add_subdirectory(${CMAKE_SOURCE_DIR}/QDataBase)
add_subdirectory(${CMAKE_SOURCE_DIR}/QDataBase/QDBLibrary)
add_subdirectory(${CMAKE_SOURCE_DIR}/TinyORM)