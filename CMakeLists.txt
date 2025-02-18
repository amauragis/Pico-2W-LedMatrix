cmake_minimum_required(VERSION 3.13)

set(NAME pico-2w-ledmatrix)

set(PICO_SDK_PATH "${CMAKE_SOURCE_DIR}/vendor/pico-sdk")
set(FREERTOS_KERNEL_PATH "${CMAKE_SOURCE_DIR}/vendor/rpi-freertos-kernel")

set(PICO_BOARD "pico2_w")
set(PICO_PLATFORM "rp2350-arm-s")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/pico_sdk_import.cmake)

project(${NAME} LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 26)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

pico_sdk_init()

include(${CMAKE_CURRENT_LIST_DIR}/port/pico_config/pico_config.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/port/freertos_config/freertos_config.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/FreeRTOS_Kernel_import.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/port/lwip/lwip_port.cmake)


add_executable(${NAME})

target_sources(${NAME} PRIVATE
    src/main.cpp
    src/ping/ping.c
)

target_include_directories(${NAME} PRIVATE
    src/ping

)

message(STATUS "PICO_LWIP_CONTRIB_PATH: ${PICO_LWIP_CONTRIB_PATH}")


target_compile_definitions(${NAME} PRIVATE
    WIFI_SSID=\"${WIFI_SSID}\"
    WIFI_PASSWORD=\"${WIFI_PASSWORD}\"

)

target_link_libraries(${NAME}
    pico_config
    freertos_config
    lwip_port
    pico_cyw43_arch_lwip_sys_freertos
    pico_stdlib
    pico_lwip_iperf
    FreeRTOS-Kernel-Heap4
)

# target_link_libraries(${NAME} pico_stdlib)
# target_link_libraries(${NAME} FreeRTOS-Kernel-Heap4)
# target_link_libraries(${NAME} pico_config)
# target_link_libraries(${NAME} freertos_config)
# target_link_libraries(${NAME} lwip_port)

# target_link_libraries(${NAME} pico_lwip)
# target_link_libraries(${NAME} pico_cyw43_arch_lwip_sys_freertos)
# # target_link_libraries(${NAME} pico_lwip_iperf)

target_compile_definitions(${NAME} PRIVATE
    PICO_DEFAULT_UART_TX_PIN=16
    PICO_DEFAULT_UART_RX_PIN=17
)

pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${NAME})

# set(FREERTOS_PORT "GCC_ARM_CM33_NTZ_NONSECURE" CACHE STRING "" FORCE)
# add_subdirectory(${FREERTOS_KERNEL_PATH})

# add_compile_definitions(PICO_STDIO_STACK_BUFFER_SIZE=256)

# add_executable(pico-2w-ledmatrix
# RP2040matrixDemo.c
# hub75.c ps_hub75_128.pio ps_hub75_64.pio
# gol.c pong.c
# LEDmx.c)

# pico_generate_pio_header(pico-2w-ledmatrix ${CMAKE_CURRENT_LIST_DIR}/ps_hub75_128.pio)
# pico_generate_pio_header(pico-2w-ledmatrix ${CMAKE_CURRENT_LIST_DIR}/ps_hub75_64.pio)

# pico_enable_stdio_uart(pico-2w-ledmatrix 0)
# pico_enable_stdio_usb(pico-2w-ledmatrix 1)

# target_sources(pico-2w-ledmatrix PRIVATE RP2040matrixDemo.c)

# target_include_directories(pico-2w-ledmatrix PRIVATE include/
# ${CMAKE_CURRENT_LIST_DIR}
# ${CMAKE_CURRENT_LIST_DIR}/../../Common/include)

# target_compile_definitions(pico-2w-ledmatrix PRIVATE
# PICO_DEFAULT_UART_TX_PIN=28
# PICO_DEFAULT_UART_RX_PIN=29
# PCB_LAYOUT_V1=1
# HUB75_SIZE=4040         # 4040 = 64x64, other value is 8080 for 128x128
# )

# pico_add_extra_outputs(pico-2w-ledmatrix)

# target_link_libraries(pico-2w-ledmatrix PRIVATE
# hardware_pio
# hardware_dma
# FreeRTOS-Kernel
# FreeRTOS-Kernel-Heap1
# pico_stdlib
# pico_multicore)

# add_custom_command(TARGET pico-2w-ledmatrix
# POST_BUILD
# COMMAND arm-none-eabi-size -B RP2040matrix.elf
# )

# #########################################################################
# add_executable(RP2040matrix_64_BCM
# RP2040matrixDemo.c
# hub75_BCM.c ps_hub75_128_BCM.pio ps_hub75_64_BCM.pio
# gol.c pong.c
# LEDmx.c)

# pico_generate_pio_header(RP2040matrix_64_BCM ${CMAKE_CURRENT_LIST_DIR}/ps_hub75_128_BCM.pio)
# pico_generate_pio_header(RP2040matrix_64_BCM ${CMAKE_CURRENT_LIST_DIR}/ps_hub75_64_BCM.pio)
# pico_enable_stdio_uart(RP2040matrix_64_BCM 0)
# pico_enable_stdio_usb(RP2040matrix_64_BCM 1)

# target_sources(RP2040matrix_64_BCM PRIVATE RP2040matrixDemo.c)
# target_include_directories(RP2040matrix_64_BCM PRIVATE include/
# ${CMAKE_CURRENT_LIST_DIR}
# ${CMAKE_CURRENT_LIST_DIR}/../../Common/include)
# target_compile_definitions(RP2040matrix_64_BCM PRIVATE
# PICO_DEFAULT_UART_TX_PIN=28
# PICO_DEFAULT_UART_RX_PIN=29
# HUB75_BCM=1
# PCB_LAYOUT_V2=1
# HUB75_SIZE=4040         # 4040 = 64x64, other value is 8080 for 128x128
# )
# pico_add_extra_outputs(RP2040matrix_64_BCM)
# target_link_libraries(RP2040matrix_64_BCM PRIVATE
# hardware_pio
# hardware_dma
# FreeRTOS-Kernel
# FreeRTOS-Kernel-Heap1
# pico_stdlib
# pico_multicore)
# add_custom_command(TARGET RP2040matrix_64_BCM
# POST_BUILD
# COMMAND arm-none-eabi-size -B RP2040matrix_64_BCM.elf
# )

# #########################################################################
# add_executable(RP2040matrix_128_BCM
# RP2040matrixDemo.c
# hub75_BCM.c ps_hub75_128_BCM.pio ps_hub75_64_BCM.pio
# gol.c pong.c
# LEDmx.c)

# pico_generate_pio_header(RP2040matrix_128_BCM ${CMAKE_CURRENT_LIST_DIR}/ps_hub75_128_BCM.pio)
# pico_generate_pio_header(RP2040matrix_128_BCM ${CMAKE_CURRENT_LIST_DIR}/ps_hub75_64_BCM.pio)
# pico_enable_stdio_uart(RP2040matrix_128_BCM 0)
# pico_enable_stdio_usb(RP2040matrix_128_BCM 1)

# target_sources(RP2040matrix_128_BCM PRIVATE RP2040matrixDemo.c)
# target_include_directories(RP2040matrix_128_BCM PRIVATE include/
# ${CMAKE_CURRENT_LIST_DIR}
# ${CMAKE_CURRENT_LIST_DIR}/../../Common/include)
# target_compile_definitions(RP2040matrix_128_BCM PRIVATE
# PICO_DEFAULT_UART_TX_PIN=28
# PICO_DEFAULT_UART_RX_PIN=29
# HUB75_BCM=1
# PCB_LAYOUT_V2=1
# HUB75_SIZE=8080         # 4040 = 64x64, other value is 8080 for 128x128
# )
# pico_add_extra_outputs(RP2040matrix_128_BCM)
# target_link_libraries(RP2040matrix_128_BCM PRIVATE
# hardware_pio
# hardware_dma
# FreeRTOS-Kernel
# FreeRTOS-Kernel-Heap1
# pico_stdlib
# pico_multicore)
# add_custom_command(TARGET RP2040matrix_128_BCM
# POST_BUILD
# COMMAND arm-none-eabi-size -B RP2040matrix_128_BCM.elf
# )
