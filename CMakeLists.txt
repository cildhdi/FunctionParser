cmake_minimum_required(VERSION 3.0.0)
project(function_parsing VERSION 0.1.0)

add_compile_options(-std=c++11)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})

aux_source_directory(. SRC)
add_executable(fp_test ${SRC})
target_link_libraries(fp_test ${GTEST_LIBRARY} pthread)
