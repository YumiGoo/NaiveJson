cmake_minimum_required (VERSION 2.6)
project (naivejson_test CXX)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(naivejson naivejson.cpp)
add_executable(test test.cpp)
target_link_libraries(test naivejson)