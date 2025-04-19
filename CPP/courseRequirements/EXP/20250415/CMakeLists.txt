#[[
CMake Learn;
Contact Module;
Author: greenhandzdl;
Date: 2025-04-19;
]]#

cmake_minimum_required(VERSION 4.0) # Adjust the version as needed

project(contact
    VERSION 1.0
    DESCRIPTION "通信录程序"
    HOMEPAGE_URL "https://github.com/greenhandzdl/others"
    LANGUAGES CXX #什么语言写的
)
 
# add_subdirectory(src) # Add the src dir to the search path

# add_definitions(-DDEBUG) # Add a preprocessor definition
# DEBUG

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23) # C++23 standard
# -D CMAKE_CXX_STANDARD=23

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build) # Set the output directory for executables
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib) # Set the output directory for libraries

# list(APPEND <list> <item>) # Add the cmake dir to the search path
# list(REMOVE_ITEM|REMOVE_AT <list> <item>) # Remove the item from the list
# list(LENGTH <list> <output>) # Get the length of the list
# list(GET <list> <index> <output>) # Get the item at the specified index
# list(JOIN <list> <separator> <output>) # Join the items in the list with the specified separator
# list(FIND <list> <item> <output>) # Find the index of the specified item in the list (-1)
# list(INSERT <list> <index> <item>) # Insert the item at the specified index
# list(PREPEND <list> <item>) # Prepend the item to the beginning of the list
# list(POP_BACK/POP_FRONT <list> <output>) # Remove the last item from the list
# list(SORT <list> [ASCENDING|DESCENDING]) # Sort the list

# message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}") STATUS|WARNING|SEND_ERROR|FATAL_ERROR

# PROJECT_SOURCE_DIR 项目源文件目录(camke dir),dir
# CMAKE_CURRENT_SOURCE_DIR 当前源文件目录
# Find the required libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# aux_source_directory(./ DIR_SRCS) # Get all source files in the current directory
# file(GLOB DIR_SRCS "*.cpp") # Get all source files in the current directory
# file(GLOB_RECURSE DIR_SRCS "*.h") # Get all source files in the current directory

file(GLOB_RECURSE DIR_SRCS "*.cpp") # Get all source files in the current directory
add_library(contact SHARED # SHARED or STATIC
    ${DIR_SRCS}
)


# link_directories(contact) # (Path)
# link_libraries(contact) # 

# add_executable(contact_main contact_main.cpp) blank or ;

# link_directories(contact) # (Path)
# target_link_libraries(target PUBLIC|PRIVATE|INTERFACE dest) #

# Install rules
# TARGETS 目标文件
# DESTINATION 安装路径
# install(TARGETS contact DESTINATION lib) 
# FILES 安装单个文件
# 安装 contact_required.h 头文件到安装前缀下的 include 目录（如 /usr/local/include）
# install(FILES contact_required.h DESTINATION include)