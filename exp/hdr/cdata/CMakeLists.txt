cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
function (ctraceGen infile outfile row col)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${outfile}
    COMMAND test_hdr  ${infile} ${outfile} ${row} ${col}
    DEPENDS ${infile} test_hdr ${ctrace_dir})
endfunction(ctraceGen)
project(HDR_CTEST)
set(ctrace_dir "${CMAKE_CURRENT_BINARY_DIR}")
set(testdata_dir "${PROJECT_SOURCE_DIR}")
set(small_house_cdata "${testdata_dir}/small_house_data")
set(small_house_ctrace "${ctrace_dir}/small_house_data_out")
set(small_house_row "150")
set(small_house_col "100")
set(small_church_cdata "${testdata_dir}/small_church_data")
set(small_church_ctrace "${ctrace_dir}/small_church_data_out")
set(small_church_row "200")
set(small_church_col "100")


ctraceGen(${small_house_cdata}  ${small_house_ctrace} ${small_house_row} ${small_house_col})
ctraceGen(${small_church_cdata}  ${small_church_ctrace} ${small_church_row} ${small_church_col})
add_custom_target(HDR_CTEST DEPENDS ${small_house_ctrace} ${small_church_ctrace})
