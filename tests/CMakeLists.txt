set(CMAKE_CXX_CLANG_TIDY clang-tidy)

# Include Google Test Framework
include(${PROJECT_SOURCE_DIR}/cmake/gtest.cmake)

# Include cmake utility functions
include(${PROJECT_SOURCE_DIR}/cmake/utilites.cmake)

add_tiss_test(${CMAKE_CURRENT_SOURCE_DIR}/tiss/tiss_vector_test.cpp)