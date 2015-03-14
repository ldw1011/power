cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(adder_synth)
set(adder_pt_script "${PROJECT_SOURCE_DIR}/pt_script.tcl")
set(adder_vcd_result "${CMAKE_CURRENT_BINARY_DIR}/add_trace.vcd")
set(adder_power_result "${CMAKE_CURRENT_BINARY_DIR}/pwr.out")
set(adder_gate_src "${CMAKE_CURRENT_BINARY_DIR}/../synth/gate/adder-final.v")
set(adder_vdp_result "${CMAKE_CURRENT_BINARY_DIR}/../gate/add_trace.vpd")
ADD_CUSTOM_COMMAND(
  OUTPUT ${adder_power_result}
  DEPENDS add_gate add_synth
  COMMAND vpd2vcd ${adder_vdp_result} ${adder_vcd_result}
  COMMAND pt_shell -f  ${adder_pt_script}
)
ADD_CUSTOM_TARGET(add_power DEPENDS ${adder_power_result} add_gate)


