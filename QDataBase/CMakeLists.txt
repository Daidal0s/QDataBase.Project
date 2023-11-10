set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)


set(SOURCE_FILES_DIR ${CMAKE_SOURCE_DIR}/QDataBase)
set(SOURCE_FILES    
        ${SOURCE_FILES_DIR}/main.cpp
        ${SOURCE_FILES_DIR}/widget.cpp
)

set(HEADER_FILES_DIR ${CMAKE_SOURCE_DIR}/QDataBase)
set(HEADER_FILES    
        ${HEADER_FILES_DIR}/widget.h
)

set(UI_FILES_DIR ${CMAKE_SOURCE_DIR}/QDataBase)
set(UI_FILES    
        ${UI_FILES_DIR}/widget.ui
)

set(TS_FILES QDataBase_ru_RU.ts)

set(PROJECT_SOURCES
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
        ${TS_FILES}
        res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QDataBase
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_add_library(QDataBase 
        PUBLIC
        compiler_flags
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QDataBase APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

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

target_link_libraries(QDataBase PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

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
