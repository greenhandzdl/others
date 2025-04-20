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
    LANGUAGES CXX
)
 


set(CMAKE_CXX_STANDARD 23) 

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

include_directories(${PROJECT_SOURCE_DIR}/src/Contact/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/Contact) # Add the src dir to the search path

link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(app main.cpp)
target_link_libraries(app contact)
