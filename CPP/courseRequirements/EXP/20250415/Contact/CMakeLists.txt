#[[
CMake Learn;
Contact Module;
Author: greenhandzdl;
Date: 2025-04-19;
]]#

cmake_minimum_required(VERSION 4.0) 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE DIR_SRCS "*.cpp") # Get all source files in the current directory
add_library(contact SHARED # SHARED or STATIC
    ${DIR_SRCS}
)