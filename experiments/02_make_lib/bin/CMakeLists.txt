cmake_minimum_required(VERSION 3.7)
project(using_lib)
add_executable(using_lib src/main.cpp)
target_link_libraries(using_lib LINK_PUBLIC hello)
