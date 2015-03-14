cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

function (avgPowerGen pwrfile fsmfile outfile)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${outfile}
    COMMAND AVG_POWER  -p ${pwrfile} -f ${fsmfile} -o ${outfile}
    DEPENDS ${pwrfile} ${fsmfile} AVG_POWER )
endfunction(avgPowerGen)

project(HDR_PWR)



set(power_dir "${PROJECT_SOURCE_DIR}")
set(avgpowertrace_dir "${CMAKE_CURRENT_BINARY_DIR}")

set(small_house_pwr "${power_dir}/small_house_pipe.out")
set(small_house_fsm "${power_dir}/small_house_pipe_fsm_data")
set(small_house_avg "${avgpowertrace_dir}/small_house_pipe_avg_pwr.npy")
set(small_church_pwr "${power_dir}/small_church_pipe.out")
set(small_church_fsm "${power_dir}/small_church_pipe_fsm_data")
set(small_church_avg "${avgpowertrace_dir}/small_church_pipe_avg_pwr.npy")

if(AVG_POWER)
else(AVG_POWER)
  add_executable(AVG_POWER IMPORTED )
  set_property(TARGET AVG_POWER PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../../../src/util/avgPower.py")
endif(AVG_POWER)
avgPowerGen(${small_house_pwr} ${small_house_fsm} ${small_house_avg})
avgPowerGen(${small_church_pwr} ${small_church_fsm} ${small_church_avg})

add_custom_target(HDR_PWR DEPENDS ${small_house_avg} ${small_church_avg})
#set_source_files_properties(${ctrace  PROPERTIES GENERATED TRUE)
