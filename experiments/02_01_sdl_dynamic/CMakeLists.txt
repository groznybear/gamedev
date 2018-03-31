cmake_minimum_required(VERSION 3.7)
project(sdldyn)
include_directories("${PROJECT_BINARY_DIR}")
add_executable(sdldyn bin/src/main.cpp)