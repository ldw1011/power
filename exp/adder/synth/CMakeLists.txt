cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(adder_synth)
set(gate_adder_src "${CMAKE_CURRENT_BINARY_DIR}/gate/adder_final.v")
set(synth_script "${PROJECT_SOURCE_DIR}/syn.tcl")
set(synopsys_dc_setup "${PROJECT_SOURCE_DIR}/.synopsys_dc.setup")
ADD_CUSTOM_COMMAND(
  OUTPUT ${gate_adder_src}
  DEPENDS add_verilog
  COMMAND ${CMAKE_COMMAND} -E copy ${synopsys_dc_setup} ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory log
  COMMAND ${CMAKE_COMMAND} -E make_directory gate
  COMMAND dc_shell-t -f  ${synth_script}
)
ADD_CUSTOM_TARGET(add_synth DEPENDS ${gate_adder_src})


