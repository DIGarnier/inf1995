
file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

add_library(marx ${SOURCES} ${HEADERS})
target_include_directories (marx PUBLIC "${CMAKE_SOURCE_DIR}/projet/lib_dir/include")
