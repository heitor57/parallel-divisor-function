cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
project(divisor-function C)
message("${CMAKE_SOURCE_DIR}")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(MPI REQUIRED)
#add_definitions(-DOMPI_SKIP_MPICXX)
#execute_process (
    #COMMAND bash -c "mpicc --showme:compile"
    #OUTPUT_VARIABLE mpi_compile
#)

#execute_process (
    #COMMAND bash -c "mpicc --showme:link"
    #OUTPUT_VARIABLE mpi_link
#)

##string(REPLACE "," " " mpi_link ${mpi_link})
#separate_arguments(mpi_link)
#separate_arguments(mpi_compile)

#message("${mpi_compile}")
#message("${mpi_link}")

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/parallel.c)
add_executable(serial-divisor-function ${SRC_FILES})
target_link_libraries(serial-divisor-function m)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/serial.c)
add_executable(parallel-divisor-function ${SRC_FILES})
#target_link_libraries(parallel-divisor-function )

target_link_libraries(parallel-divisor-function
  PRIVATE
  m
  MPI::MPI_C)
#target_compile_options(parallel-divisor-function PRIVATE "${mpi_compile}")
#target_link_options(parallel-divisor-function PRIVATE "${mpi_link}")

#target_compile_options(parallel-divisor-function PRIVATE ${MPI_C_COMPILE_FLAGS})
#target_link_options(parallel-divisor-function PRIVATE ${MPI_C_LINK_FLAGS})

