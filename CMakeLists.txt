cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(libtiss VERSION 0.0.1)

include(CTest)
enable_testing()

# Clang tidy
set(CMAKE_CXX_CLANG_TIDY clang-tidy-9)

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/)
set(LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_library(tiss SHARED
  ${LIB_SRC_DIR}/vector.c
  ${LIB_SRC_DIR}/version.c
)
target_include_directories(tiss PUBLIC ${LIB_INCLUDES})
set_property(TARGET tiss PROPERTY C_STANDARD 11)

# Include tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
