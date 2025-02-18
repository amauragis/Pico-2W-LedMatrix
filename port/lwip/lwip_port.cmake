cmake_minimum_required(VERSION 3.15)

add_library(lwip_port INTERFACE)

target_include_directories(lwip_port INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)
