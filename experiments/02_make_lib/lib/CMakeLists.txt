cmake_minimum_required(VERSION 3.7)
project(greetings_lib)
add_library(greetings_lib STATIC include/lib.hpp src/lib.cpp)
target_include_directories(greetings_lib PUBLIC
                          ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(greetings_lib PUBLIC cxx_std_17)
