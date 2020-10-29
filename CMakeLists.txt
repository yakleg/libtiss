cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(libtiss VERSION 0.0.1)

include(CTest)
enable_testing()

# Clang tidy
# Todo: make different clang-tidy setting for C and C++

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

set(LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include library 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Include tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
