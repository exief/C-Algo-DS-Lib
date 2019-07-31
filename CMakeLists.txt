cmake_minimum_required(VERSION 2.4)

option(COMPLAIN "Bitching" OFF)
if(CMAKE_BUILD_TYPE EQUAL "Debug")
    option(OPTIMISE "Compiler Optimisations" OFF)
else()
    option(OPTIMISE "Compiler Optimisations" ON)
endif()
option(CUDA_SUPPORT "Enabled CUDA Compute Support" OFF)
option(OPENCL_SUPPORT "Enable OpenCL Compute Support" OFF)

set (C_ALGO_LIB_NUMBER_MAJOR 0)
set (C_ALGO_LIB_NUMBER_MINOR 0.1)

project(C_ALGO_LIB)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(FATAL_ERROR "DARWIN/MacOS/Apple unssuported at this time. Exiting")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Compling for LINUX Based-Systems. Setting Flags...")
    add_definitions(-DPLATFORM_LINUX=1)
    add_definitions(-DPLATFORM_WIN64=0)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Compling for WINDOWS Based-Systems. Setting Flags...")
    add_definitions(-DPLATFORM_WIN64=1)
    add_definitions(-DPLATFORM_LINUX=0)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(${CMAKE_MAJOR_VERSION}  VERSION_LESS 3)
    message("Please update to CMAKE 3.1+ for more optimised build process")
endif()

if(COMPLAIN)
    message(STATUS "Bit...Complaining Enabled.  Compiler error messaged printed to screen for ${PROJECT_NAME}")
    add_definitions(-Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align
            -Wstrict-overflow=2 -Wwrite-strings -Wcast-qual -Wconversion -Wunreachable-code  -Wformat=2 -Wpedantic)
endif()
if(OPTIMISE)
    message(STATUS "Using compiler optimisations.")
    add_definitions("-O3")
endif()

if(CUDA_SUPPORT)
    if(NOT "${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
        message(FATAL_ERROR "CUDA Support required targeting X86_64. Re-run configure with X86_64 as the target build")
    else()
		enable_language(CUDA)
        find_package(CUDA REQUIRED)
        message(STATUS "CUDA support enabled")
    endif()
endif()

if(OPENCL_SUPPORT)
    if(NOT "${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
        message(FATAL_ERROR "OpenCL Support requires targeting X86_64. Re-run configure with X86_64 as the target build")
    else()
        find_package(OpenCL)
        if(NOT OpenCL_FOUND)
            message(FATAL_ERROR "Failed to find the OpenCL libraries")
        endif()
        if(KURO_DESKTOP)
            include_directories($ENV{OCL_ROOT})
        else()
            include_directories(${OpenCL_INCLUDE_DIRS})
        endif()
		add_definitions(-DOpenCL=1)
    endif()
endif()

find_package(Threads REQUIRED)

if(!${CMAKE_THREAD_LIBS_INIT})
    message(FATAL_ERROR "Couldnt find a Threading LIbrary. Aborting.")
else()
    message(STATUS "Found Threading Library: ${CMAKE_THREAD_LIBS_INIT}")
endif()

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if(OPENCL_SUPPORT)
    file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernels)
# need to do this per cl file configure_file(path ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernels COPYONLY)
endif()

set(SOURCES src/suffix-trie/Suffix-Trie.h
            src/suffix-trie/Suffix-Trie.c)

add_library(C_ALGO_LIB SHARED ${SOURCES})

if(CUDA_SUPPORT)
    set(CUDA_SEPERABLE_COMPILATION ON)
    set(BUILD_SHARED_LIBS OFF)
	set(CUDA_PROPOGATE_HOST_FLAGS OFF)
	set(CUDA_HOST_COMPILER gcc)
    #file(CUDA_FILES CUDAKernels/Test.cu)
	list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_61,code=sm_61")
	CUDA_COMPILE(CU_O
			gpu/cuda/Test.cu
			gpu/cuda/EntangledU.cu
			)

	cuda_add_library(CUDA_C_ALGO_LIB ${SOURCES} ${CU_O} )
endif()