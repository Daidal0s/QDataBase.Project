set(TINY_ORM_HEADER_FILES_DIR ${CMAKE_SOURCE_DIR}/TinyORM/include/orm)
set(HEADER_FILES_DIRS headers
                      ${TINY_ORM_HEADER_FILES_DIR}
)

set(SOURCE_FILES_DIR src)
set(SOURCE_FILES ${SOURCE_FILES_DIR}/QDBLibrary.cpp)


add_library(QDBLibrary STATIC ${SOURCE_FILES})
target_link_libraries(QDBLibrary PUBLIC ${TinyOrm_target})
target_precompile_headers(QDBLibrary PRIVATE pch.h)