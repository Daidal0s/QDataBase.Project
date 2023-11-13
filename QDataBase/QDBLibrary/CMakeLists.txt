set(TINY_ORM_HEADER_FILES_DIR ${CMAKE_SOURCE_DIR}/TinyORM/include/orm)
set(HEADER_FILES_DIRS headers
                      ${TINY_ORM_HEADER_FILES_DIR}
)

set(SOURCE_FILES_DIR src)
set(SOURCE_FILES ${SOURCE_FILES_DIR}/QDBLibrary.cpp)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)

qt_add_library(QDBLibrary STATIC ${SOURCE_FILES})
target_link_libraries(QDBLibrary PRIVATE Qt6::Core)
target_include_directories(QDBLibrary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(QDBLibrary PRIVATE pch.h)