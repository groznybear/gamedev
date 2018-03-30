cmake_minimum_required(VERSION 3.7)
project(hello)
add_library(hello SHARED src/lib.cpp) #or# add_library(hello STATIC src/lib.cpp) 
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)