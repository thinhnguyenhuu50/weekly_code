cmake_minimum_required(VERSION 3.15)

# Set the project name
project(weekly_code VERSION 0.1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable for your project
add_executable(weekly_code main.cpp)

# ====================================================

# Add additional library names
set(libs_list week9)

# Add subdirectories for all libraries
foreach(lib ${libs_list})
    add_subdirectory(inc/${lib})
endforeach()

# Link all libraries
target_link_libraries(weekly_code ${libs_list})

# Include directories for the libraries
target_include_directories(weekly_code PUBLIC "${PROJECT_BINARY_DIR}")

