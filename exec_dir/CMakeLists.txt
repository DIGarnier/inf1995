
file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories (${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/projet/lib_dir/include")
target_link_libraries(${PROJECT_NAME} ${LIB_NAME})
