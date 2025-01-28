set(NAME hello_world)

add_executable(${NAME}
    hello_world.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${NAME} pico_stdlib)

pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${NAME})

# # Set up files for the release packages
# install(FILES
#     ${CMAKE_CURRENT_BINARY_DIR}/src/${NAME}/${NAME}.uf2
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
# )
