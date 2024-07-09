cmake_minimum_required(VERSION 3.10)
project(CustomArrayProject)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add options for variadic compilation
option(BUILD_CUSTOM_ARRAY "Build the custom array implementation" ON)
option(BUILD_MAIN "Build the main program" ON)
option(BUILD_BENCHMARK "Build the benchmarking program" OFF)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(CUSTOM_ARRAY_SOURCES
    custom_array.c
    error_handling.c
)

# Conditional compilation for custom array
if(BUILD_CUSTOM_ARRAY)
    add_library(custom_array STATIC ${CUSTOM_ARRAY_SOURCES})
endif()

# Conditional compilation for main program
if(BUILD_MAIN)
    add_executable(main main.c)
    target_link_libraries(main PRIVATE custom_array pthread)
endif()

# Conditional compilation for benchmarking
if(BUILD_BENCHMARK)
    add_executable(benchmark benchmark.cpp)
    target_link_libraries(benchmark PRIVATE custom_array pthread)
endif()

