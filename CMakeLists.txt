cmake_minimum_required(VERSION 3.10)
project(CustomArrayProject)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the custom array library
add_library(custom_array STATIC custom_array.c)

# Add the executable for the main program
add_executable(main main.c)

# Link the custom array library to the main executable
target_link_libraries(main PRIVATE custom_array)

