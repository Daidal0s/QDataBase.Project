set(HEADER_FILES_DIR headers)
set(MODELS_FILES_DIR models)
set(SOURCE_FILES_DIR src)

set(SOURCE_FILES ${SOURCE_FILES_DIR}/QDBLibrary.cpp)

add_library(QDBLibrary STATIC ${SOURCE_FILES})
target_precompile_headers(QDBLibrary PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers/stdafx.h)
target_include_directories(QDBLibrary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                                      PUBLIC ${HEADER_FILES_DIR} 
                                      PUBLIC ${MODELS_FILES_DIR}
)
target_link_libraries(QDBLibrary PUBLIC compiler_flags
                                 PRIVATE Qt6::Core
                                 PRIVATE TinyOrm::TinyOrm
)
target_link_directories(QDBLibrary PUBLIC models
)
# target_precompile_headers(QDBLibrary PRIVATE stdafx.h)