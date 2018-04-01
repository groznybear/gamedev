cmake_minimum_required(VERSION 3.7)
project(sdllib)

add_executable(${PROJECT_NAME} bin/src/main.cpp)

if(APPLE)
find_library(SDL2_LIB libSDL2.dylib HINTS "/WORK/itacademy/custom/lib")
elseif(UNIX)
find_library(SDL2_LIB libSDL2.so)
endif()

if(NOT SDL2_LIB)
  message(FATAL_ERROR "SDL2 library not found")
else()
  message(STATUS "SDL2 found at: ${SDL2_LIB}")
  target_link_libraries(${PROJECT_NAME} ${SDL2_LIB})
endif()
