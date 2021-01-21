# cmake_minimum_required(VERSION <specify CMake version here>)
project(mytable.wasm)
cmake_minimum_required(VERSION 3.5)
#execute_process(COMMAND xdev build)
#add_executable(mytable.wasm -)
#add_custom_command(
#        OUTPUT  ./
#        COMMAND xdev build
#        WORKING_DIRECTORY ./
#        COMMENT
#        "Unpacking C++ wrappers for BLAS/LAPACK"
#)

include_directories("/root/xuperchain/core/contractsdk/cpp/src")
add_custom_target(mytable.wasm)