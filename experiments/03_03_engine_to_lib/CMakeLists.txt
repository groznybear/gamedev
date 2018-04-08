cmake_minimum_required(VERSION 3.7)
project(microengine)

add_executable(${PROJECT_NAME} main.cpp)

if(APPLE)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
find_library(SDL2_LIB libSDL2d.dylib)
else()
find_library(SDL2_LIB libSDL2.dylib)
endif()
endif(APPLE)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB})