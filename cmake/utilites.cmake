# -------------------------- add_test_target function -------------------------

function(add_target file_name)
    get_filename_component(target_name "${file_name}" NAME_WE)

    add_executable("${target_name}" "")
    target_include_directories("${target_name}" PRIVATE ${LIB_INCLUDES})
    target_sources("${target_name}" PRIVATE "${file_name}")
    target_compile_options("${target_name}" PRIVATE -Wall -Werror -fsanitize=address)
    target_link_libraries("${target_name}" asan utilites pthread)

    set_property(TARGET "${target_name}" PROPERTY C_STANDARD 11)
endfunction(add_target)

# -------------------------- add_test_target function -------------------------
