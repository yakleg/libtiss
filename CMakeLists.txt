cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(libtiss VERSION 0.0.1)

include(CTest)
enable_testing()

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/)
set(LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Include cmake utility functions
include(${PROJECT_SOURCE_DIR}/cmake/utilites.cmake)

# Include Google Test Framework
include(cmake/gtest.cmake)


add_library(tiss SHARED 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/version.c)
target_include_directories(tiss PRIVATE ${LIB_INCLUDE})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
