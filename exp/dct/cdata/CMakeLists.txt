cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
function (dctCtraceGen test_type outfile)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${outfile}
    COMMAND test_dct  ${test_type} ${outfile}
    DEPENDS test_dct)
endfunction(dctCtraceGen)

project(DCT_TEST)
set(roki_flag "r")
set(roki_output "roki_trace")
set(audi_flag "a")
set(audi_output "audi_trace")
set(lena_flag "l")
set(lena_output "lena_trace")

dctCtraceGen(${roki_flag} ${roki_output})
dctCtraceGen(${audi_flag} ${audi_output})
#dctCtraceGen(${lena_flag} ${lena_output})



add_custom_target(DCT_TEST DEPENDS ${roki_output}  ${audi_output})  #${lena_output})
