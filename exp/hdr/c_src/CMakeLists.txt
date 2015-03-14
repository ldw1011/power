cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(hdr)
# executable
if(HLS_INCLUDE)
  include_directories(${HLS_INCLUDE})
else(HLS_INCLUDE)
  IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories("/User")
  else(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(HLS_INCLUDE "/home/polaris/dlee/iccad/include/hls")
    include_directories(${HLS_INCLUDE})
  endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
endif(HLS_INCLUDE)

add_executable(test_hdr computeWeight.cpp test.cpp)

#set(small_house_data "${PROJECT_SOURCE_DIR}/../testvector/small_house_data")
#set(ctrace "${CMAKE_CURRENT_BINARY_DIR}/small_house_data_out")


#add_custom_target(hdr DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${ctrace_name}" test_hdr)
