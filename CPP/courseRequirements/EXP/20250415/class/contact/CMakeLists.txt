cmake_minimum_required(VERSION 3.10)

project(ContactModule)

set(CMAKE_CXX_STANDARD 17)

add_library(contact SHARED
    contact_required.h
    contact.cpp
    # Add other source files here if needed
)

# Specify include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Optionally, link against other libraries
# target_link_libraries(contact <other_libraries>)

# Install rules
install(TARGETS contact DESTINATION lib)
install(FILES contact_required.h DESTINATION include)