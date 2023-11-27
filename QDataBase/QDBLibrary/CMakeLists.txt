set(HEADER_FILES_DIR headers)
set(SOURCE_FILES_DIR src)

set(SOURCE_FILES ${SOURCE_FILES_DIR}/QDBLibrary.cpp)

add_library(QDBLibrary STATIC ${SOURCE_FILES})
target_include_directories(QDBLibrary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                                      PUBLIC ${HEADER_FILES_DIR}                                
)
target_link_libraries(QDBLibrary PUBLIC compiler_flags
                                 PRIVATE Qt6::Core
                                 PRIVATE TinyOrm::TinyOrm
)
target_link_directories(QDBLibrary PUBLIC models)
# target_precompile_headers(QDBLibrary PRIVATE pch.h)