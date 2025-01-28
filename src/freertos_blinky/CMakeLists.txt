set(NAME freertos_blinky)

add_executable(${NAME}
    main.cpp
    Agent.cpp
    BlinkWAgent.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${NAME} pico_stdlib )
target_link_libraries(${NAME} freertos_config FreeRTOS-Kernel-Heap4 pico_cyw43_arch_none)


pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${NAME})

# # Set up files for the release packages
# install(FILES
#     ${CMAKE_CURRENT_BINARY_DIR}/src/${NAME}/${NAME}.uf2
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
# )
