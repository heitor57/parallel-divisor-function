cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
project(divisor-function C)

#set(CMAKE_CXX_FLAGS_RELEASE "-fno-reorder-functions" "-fno-inline" "-no-pie")
#set(CMAKE_C_FLAGS_RELEASE "-fno-reorder-functions" "-fno-inline" "-no-pie")

#add_definitions(-DDEBUG)
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DENABLE_DEBUG_MACRO")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_DEBUG_MACRO")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
#add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")
#message("${CMAKE_SOURCE_DIR}")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
find_package(MPI REQUIRED)

add_definitions(-DNDEBUG)
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
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/parallel_hybrid.c)
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/serial_blocks.c)
add_executable(serial-df ${SRC_FILES})
#target_link_libraries(serial-df m)
target_link_libraries(serial-df
  PRIVATE
  m
  MPI::MPI_C)
target_compile_options(serial-df PRIVATE -O3)
#target_compile_options(serialdf PRIVATE -pg -g)
#target_link_options(serialdf PRIVATE -pg -g)

#target_compile_definitions(serialdf PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")

#file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/parallel.c)
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/serial.c)
#add_executable(serial-blocks-divisor-function ${SRC_FILES})
#target_link_libraries(serial-blocks-divisor-function m)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/serial_blocks.c)
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/serial.c)
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/parallel_hybrid.c)
add_executable(parallel-df ${SRC_FILES})
target_link_libraries(parallel-df
  PRIVATE
  m
  MPI::MPI_C)
target_compile_options(parallel-df PRIVATE -O3)
#target_compile_options(paralleldf PRIVATE "${mpi_compile}")
#target_link_options(paralleldf PRIVATE "${mpi_link}")

#target_compile_options(paralleldf PRIVATE ${MPI_C_COMPILE_FLAGS})
#target_link_options(paralleldf PRIVATE ${MPI_C_LINK_FLAGS})


file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/serial_blocks.c)
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/serial.c)
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/parallel.c)

find_package(OpenMP)
if (OPENMP_FOUND)
    add_executable(parallel-hybrid-df ${SRC_FILES})
    target_link_libraries(parallel-hybrid-df
      PRIVATE
      m
      MPI::MPI_C)
    #target_compile_options(parallel-hybrid-df PRIVATE -O3)
    #add_executable(parallel-hybrid-df ${SRC_FILES})
    target_compile_options(parallel-hybrid-df PRIVATE -O3 -Wall -DPARALLEL -fopenmp)
    target_link_options(parallel-hybrid-df PRIVATE -fopenmp)
endif()
