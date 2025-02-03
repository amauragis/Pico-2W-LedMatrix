cmake_minimum_required(VERSION 3.15)

add_library(pico_config INTERFACE)

target_include_directories(pico_config INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(pico_config INTERFACE
    PICO_STDIO_STACK_BUFFER_SIZE=128
)
target_link_libraries(pico_config INTERFACE
    pico_stdlib
)
