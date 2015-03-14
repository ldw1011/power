cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(gate_test_add)

set(gate_lib_file "/home/polaris/dlee/.local/synopsys_db/NangateOpenCellLibrary.v")
set(adder_vpd_result "${CMAKE_CURRENT_BINARY}/adder_trace.vpd")
set(adder_src "${CMAKE_CURRENT_BINARY_DIR}/../synth/gate/adder-final.v")
set(test_add_src "${CMAKE_CURRENT_BINARY_DIR}/../verilog/test_add.v")
set(dump_tcl "${PROJECT_SOURCE_DIR}/dump_waveform.cmds")
set(ivector "${PROJECT_SOURCE_DIR}/../verilog/ivector.txt")
#set(TARGET VLOGAN PROPERTIES IMPORTED_LOCATION "vlogan")
ADD_CUSTOM_COMMAND(
  OUTPUT ${adder_vpd_result}
  DEPENDS ${adder_src}
  COMMAND vlogan ${adder_src}
  COMMAND vlogan ${test_add_src}
  COMMAND vlogan ${gate_lib_file}  +delay_mode_zero +notimingcheck
  COMMAND vcs test_add -l comp.log +lint=PCWM -debug_pp -full64 -ignore all
  COMMAND ${CMAKE_COMMAND} -E copy ${ivector} ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ./simv +vcs+nostdout -ucli -do ${dump_tcl}
  )
ADD_CUSTOM_TARGET(add_gate DEPENDS add_synth ${adder_vpd_result})


