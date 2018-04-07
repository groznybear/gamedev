cmake_minimum_required(VERSION 3.7)
project(mainloop)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if(APPLE)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
find_library(SDL2 libSDL2d.dylib)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
target_link_libraries(${PROJECT_NAME} ${SDL2})
endif(APPLE)