cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

function (avgPowerGen pwrfile fsmfile outfile)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${outfile}
    COMMAND AVG_POWER  -p ${pwrfile} -f ${fsmfile} -o ${outfile}
    DEPENDS ${pwrfile} ${fsmfile} AVG_POWER )
endfunction(avgPowerGen)

project(GEMM_PWR)



set(power_dir "${PROJECT_SOURCE_DIR}")
set(avgpowertrace_dir "${CMAKE_CURRENT_BINARY_DIR}")

set(300_pwr "${power_dir}/300_pipe.out")
set(300_fsm "${power_dir}/300_pipe_fsm_data")
set(300_avg "${avgpowertrace_dir}/300_pipe_avg_pwr.npy")
set(3000_pwr "${power_dir}/3000_pipe.out")
set(3000_fsm "${power_dir}/3000_pipe_fsm_data")
set(3000_avg "${avgpowertrace_dir}/3000_pipe_avg_pwr.npy")

if(AVG_POWER)
else(AVG_POWER)
  add_executable(AVG_POWER IMPORTED )
  set_property(TARGET AVG_POWER PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../../../src/util/avgPower.py")
endif(AVG_POWER)
avgPowerGen(${300_pwr} ${300_fsm} ${300_avg})
avgPowerGen(${3000_pwr} ${3000_fsm} ${3000_avg})

add_custom_target(GEMM_PWR DEPENDS ${300_avg} ${3000_avg})
#set_source_files_properties(${ctrace  PROPERTIES GENERATED TRUE)
