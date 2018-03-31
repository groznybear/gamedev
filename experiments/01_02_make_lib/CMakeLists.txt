#Based on SFML documentation
cmake_minimum_required(VERSION 3.7)
project(use_lib)

# The version number
set(use_lib_VERSION_MAJOR 1)
set(use_lib_VERSION_MINOR 1)

if(APPLE)
set(use_lib_PLATFORM "OS X")
elseif(UNIX)
set(use_lib_PLATFORM "LINUX")
elseif(WIN32)
set(use_lib_PLATFORM "WIN32")
endif(APPLE)



# add the binary tree to the search path for include files
# so that we will find main.h
include_directories("${PROJECT_BINARY_DIR}")

option (HELLOLIB "Use separate lib for greetings" ON)

# add the hello lib library?
if (HELLOLIB)
  include_directories ("${PROJECT_SOURCE_DIR}/lib")
  add_subdirectory (lib)
  set (EXTRA_LIBS ${EXTRA_LIBS} hello)
endif (HELLOLIB)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/bin/src/mainconfig.hpp.in"
    "${PROJECT_BINARY_DIR}/mainconfig.hpp"
    @ONLY
)

# add the executable
add_executable(use_lib bin/src/main.cpp)
target_link_libraries (use_lib ${EXTRA_LIBS})