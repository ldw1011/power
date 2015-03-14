cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

function (avgPowerGen pwrfile fsmfile outfile)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${outfile}
    COMMAND AVG_POWER  -p ${pwrfile} -f ${fsmfile} -o ${outfile}
    DEPENDS ${pwrfile} ${fsmfile} AVG_POWER )
endfunction(avgPowerGen)

project(DCT)



set(power_dir "${PROJECT_SOURCE_DIR}")
set(avgpowertrace_dir "${CMAKE_CURRENT_BINARY_DIR}")

set(roki_pwr "${power_dir}/roki_pipe.out")
set(roki_fsm "${power_dir}/roki_pipe_fsm_data")
set(roki_avg "${avgpowertrace_dir}/roki_pipe_avg_pwr.npy")
set(audi_pwr "${power_dir}/audi_pipe.out")
set(audi_fsm "${power_dir}/audi_pipe_fsm_data")
set(audi_avg "${avgpowertrace_dir}/audi_pipe_avg_pwr.npy")

if(AVG_POWER)
else(AVG_POWER)
  add_executable(AVG_POWER IMPORTED )
  set_property(TARGET AVG_POWER PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../../../src/util/avgPower.py")
endif(AVG_POWER)
avgPowerGen(${roki_pwr} ${roki_fsm} ${roki_avg})
avgPowerGen(${audi_pwr} ${audi_fsm} ${audi_avg})

add_custom_target(DCT_PWR DEPENDS ${roki_avg} ${audi_avg})
#set_source_files_properties(${ctrace  PROPERTIES GENERATED TRUE)
