cmake_minimum_required(VERSION 3.0.0)
project(FunctionParser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

#library
aux_source_directory(src SRC)
add_library(FunctionParser ${SRC})

#test
find_package(GTest REQUIRED)
if(GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIR})
    add_executable(FunctionParserTest test/test.cpp)
    target_link_libraries(FunctionParserTest FunctionParser GTest::GTest)
    add_test(FunctionParserTest FunctionParserTest)
endif(GTEST_FOUND)
