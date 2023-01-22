cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(light
  light.c
)

pico_enable_stdio_usb(light 1)
pico_enable_stdio_uart(light 1)

pico_add_extra_outputs(light)

target_link_libraries(light pico_stdlib)

add_executable(button
  button.c
)

pico_enable_stdio_usb(button 1)
pico_enable_stdio_uart(button 1)

pico_add_extra_outputs(button)

target_link_libraries(button pico_stdlib)