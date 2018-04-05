cmake_minimum_required(VERSION 3.7)
project(sdllib)

add_executable(${PROJECT_NAME} bin/src/main.cpp)

if(APPLE)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
find_library(SDL2_LIB libSDL2d.dylib)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#find_library(SDL2_LIB SDL2)
#endif(CMAKE_BUILD_TYPE STREQUAL "Release")
endif(APPLE)

if(NOT SDL2_LIB)
  message(STATUS "SDL2 library not found")
else()
  message(STATUS "SDL2 found at: ${SDL2_LIB}")
  target_link_libraries(${PROJECT_NAME} ${SDL2_LIB})
endif()
