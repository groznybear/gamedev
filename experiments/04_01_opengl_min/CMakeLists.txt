cmake_minimum_required(VERSION 3.7)

if(APPLE)
project(microengine_osx)
elseif(UNIX)
project(microengine_linux)
elseif(WIN32)
project(microengine_win32)
endif()

set(CMAKE_CXX_FLAGS "-std=c++17")

if(CMAKE_BUILD_TYPE STREQUAL "")
set(CMAKE_BUILD_TYPE "Release")
endif()

if(APPLE) #SDL2
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
find_library(SDL2_LIB
             NAMES SDL2
             HINTS CMAKE_SYSTEM_LIBRARY_PATH)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
find_library(SDL2_LIB
             NAMES SDL2
             HINTS CMAKE_SYSTEM_LIBRARY_PATH)
endif()
elseif(UNIX) #SDL2
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
find_library(SDL2_LIB
             NAMES SDL2
             HINTS CMAKE_SYSTEM_LIBRARY_PATH)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
find_library(SDL2_LIB
             NAMES SDL2
             HINTS CMAKE_SYSTEM_LIBRARY_PATH)
endif()

endif(APPLE)
# If SDL2 was not found, there no reason to continue
if(NOT SDL2_LIB)
message(FATAL_ERROR "SDL2 lib was not found. Abort...")
endif()

# Making separate lib from engine files
add_library(engine_lib engine.cpp)
target_compile_features(engine_lib
                        PUBLIC cxx_std_17)
# Linking SDL2 to engine lib

if(APPLE) #OpenGL
target_link_libraries(engine_lib ${SDL2_LIB})
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
message(STATUS "OPENGL :: OK")
target_link_libraries(engine_lib ${OPENGL_INCLUDE_DIR})
endif()
elseif(UNIX)
target_link_libraries(engine_lib
               -lSDL2
               -lGL
               )
endif()
# Linking engine lib to main "game" file
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} engine_lib)