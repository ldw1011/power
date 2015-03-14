cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(HDR)

add_subdirectory(c_src)
add_subdirectory(cdata)
add_subdirectory(pwr)
message("${small_house_avg}")
add_custom_target(HDR DEPENDS test_hdr HDR_PWR HDR_CTEST)
