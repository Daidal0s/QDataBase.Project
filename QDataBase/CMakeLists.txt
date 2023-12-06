set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(DEV_BUILD "adds some dev shit" ON)

set(SOURCE_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_FILES    
        ${SOURCE_FILES_DIR}/main.cpp
        ${SOURCE_FILES_DIR}/widget.cpp
        ${SOURCE_FILES_DIR}/dev.cpp
)

set(HEADER_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)
set(HEADER_FILES    
        ${HEADER_FILES_DIR}/widget.h
        ${HEADER_FILES_DIR}/dev.h
)

set(UI_FILES_DIR ${SOURCE_FILES_DIR})
set(UI_FILES    
        ${UI_FILES_DIR}/widget.ui
        ${UI_FILES_DIR}/dev.ui
)

set(TS_FILES QDataBase_ru_RU.ts)

set(PROJECT_SOURCES
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
        ${TS_FILES}
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QDataBase
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res.qrc
    )

    if(DEV_BUILD)
        target_compile_definitions(QDataBase PRIVATE DEV_BUILD)
    endif()

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(QDataBase SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QDataBase
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_include_directories(QDataBase PRIVATE ${HEADER_FILES_DIR})
target_precompile_headers(QDataBase PRIVATE ${HEADER_FILES_DIR}/stdafx.h)
target_link_libraries(QDataBase PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                PRIVATE Qt${QT_VERSION_MAJOR}::Sql
                                PRIVATE qtcsv
                                PRIVATE QDBLibrary
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QDataBase)
endif()
set_target_properties(QDataBase PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QDataBase
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QDataBase)
endif()
