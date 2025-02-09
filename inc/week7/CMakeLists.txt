# Extract the name of the current directory
get_filename_component(LIB_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB SOURCE_FILES "*.cpp")
add_library(${LIB_NAME} ${SOURCE_FILES})
target_include_directories(${LIB_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")