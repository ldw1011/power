cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(test_add)

#set(TARGET VLOGAN PROPERTIES IMPORTED_LOCATION "vlogan")
set(orig_test_src "${PROJECT_SOURCE_DIR}/test_add.v")
set(orig_adder_src "${PROJECT_SOURCE_DIR}/adder.v")
set(adder_src "${CMAKE_CURRENT_BINARY_DIR}/adder.v")
ADD_CUSTOM_COMMAND(
  OUTPUT ${adder_src}
  COMMAND ${CMAKE_COMMAND} -E copy ${orig_adder_src} ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy ${orig_test_src} ${CMAKE_CURRENT_BINARY_DIR}
  # COMMAND vlogan ${adder_src}
  # COMMAND vlogan ${test_add_src}
  # COMMAND vcs test_add -l comp.log +lint=PCWM -debug_pp -full64 -ignore all
  # COMMAND ./simv +vcs+nostdout -ucli -do dump_waveform.cmds
  )
ADD_CUSTOM_TARGET(add_verilog DEPENDS ${adder_src} ${orig_test_src} ${orig_adder_src})

