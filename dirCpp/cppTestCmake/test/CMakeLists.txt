cmake_minimum_required(VERSION 2.8)
project(test)

include_directories(include)
add_library(sqr STATIC src/sqr.cpp)

add_executable(demo src/main.cpp)
target_link_libraries(demo sqr)

add_subdirectory(test)
enable_testing()
add_test(NAME mytest COMMAND Test)
