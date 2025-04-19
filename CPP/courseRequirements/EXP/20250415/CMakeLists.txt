#[[
CMake Learn;
Contact Module;
Author: greenhandzdl;
Date: 2025-04-19;
]]#

cmake_minimum_required(VERSION 4.0) 

project(contact
    VERSION 1.0
    DESCRIPTION "通信录程序"
    HOMEPAGE_URL "https://github.com/greenhandzdl/others"
    LANGUAGES CXX #什么语言写的
)
 
add_subdirectory(${PROJECT_SOURCE_DIR}/Contact) # Add the src dir to the search path

set(CMAKE_CXX_STANDARD 23) 

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)
