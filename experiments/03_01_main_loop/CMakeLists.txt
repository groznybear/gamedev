cmake_minimum_required(VERSION 3.7)
if(APPLE)
project("mainloop_osx")
elseif(UNIX)
project("mainloop_linux")
elseif(WIN32)
project("mainloop_win32")
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if(APPLE)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
find_library(SDL2_LIB libSDL2d.dylib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
find_library(SDL2_LIB libSDL2.dylib)
endif()

if(NOT APPLE)
if(UNIX)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
find_library(SDL2_LIB SDL2)
endif()
endif(UNIX)
endif()


if(NOT SDL2_LIB)
message(FATAL_ERROR "SDL2 not found")
else()
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB})
endif()


endif(APPLE)