set(CMAKE_C_CLANG_TIDY clang-tidy)

set(LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tiss)

set(LIB_SOURCES 
  ${LIB_SRC_DIR}/vector.c
  ${LIB_SRC_DIR}/version.c
)

add_library(tiss SHARED ${LIB_SOURCES})
target_include_directories(tiss PUBLIC ${LIB_INCLUDES})
set_property(TARGET tiss PROPERTY C_STANDARD 11)


