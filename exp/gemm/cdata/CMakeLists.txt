cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(MAT_TEST)
set(300_output "300_trace")
set(3000_output "3000_trace")


ADD_CUSTOM_COMMAND(
    OUTPUT ${300_output}
    COMMAND test_mat_300  ${300_output}
    DEPENDS test_mat_300)

ADD_CUSTOM_COMMAND(
    OUTPUT ${3000_output}
    COMMAND test_mat_3000  ${3000_output}
    DEPENDS test_mat_3000)

add_custom_target(MAT_TEST DEPENDS ${3000_output}  ${300_output}) 
