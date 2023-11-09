cmake_minimum_required(VERSION 3.5)

project(QDataBase VERSION 0.1 LANGUAGES CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE
                                                 cxx_std_17)   

add_subdirectory(${CMAKE_SOURCE_DIR}/QDataBase)