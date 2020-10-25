# -------------------------- add_tiss_test function -------------------------

function(add_tiss_test file_name)
    get_filename_component(target_name "${file_name}" NAME_WE)

    add_executable("${target_name}" "")
    target_include_directories("${target_name}" PRIVATE ${LIB_INCLUDES})
    target_sources("${target_name}" PRIVATE "${file_name}")
    target_compile_options("${target_name}" PRIVATE -Wall -Werror -fsanitize=address)
    target_link_libraries("${target_name}" PRIVATE gtest_main asan tiss)

    set_property(TARGET "${target_name}" PROPERTY CXX_STANDARD 17)

    add_test(NAME "${target_name}" COMMAND "${target_name}")
endfunction(add_tiss_test)

# -------------------------- add_tiss_test function -------------------------
