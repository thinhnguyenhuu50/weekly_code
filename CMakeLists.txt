cmake_minimum_required(VERSION 3.15)

# Set the project name
project(weekly_code VERSION 0.1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable for your project
add_executable(weekly_code main.cpp)

set(lib week3)

# Add the subdirectories for libraries
add_subdirectory(inc/${lib})

# Link the libraries
target_link_libraries(weekly_code ${lib})

# Include directories for the libraries
target_include_directories(weekly_code PUBLIC "${PROJECT_BINARY_DIR}")