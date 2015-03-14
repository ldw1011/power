cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(test_dct)
add_executable(test_mat_300 matrixmul_test_300.cpp matrixmul.cpp) 
add_executable(test_mat_3000 matrixmul_test_3000.cpp matrixmul.cpp) 


