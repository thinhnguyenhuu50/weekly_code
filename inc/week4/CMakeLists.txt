# Extract the name of the current directory
get_filename_component(LIB_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_library(${LIB_NAME} w4.cpp)
target_include_directories(week4 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")