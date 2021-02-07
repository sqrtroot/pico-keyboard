cmake_minimum_required(VERSION 3.12)
set(NAME pico-keyboard)
set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/pico-sdk)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

add_executable(${NAME}
    src/main.cpp

    src/device_callbacks.c
    src/usb_descriptors.c

    src/hid_callbacks.cpp
    src/System.cpp
    src/VoltMeter.cpp
)

target_include_directories(${NAME} PRIVATE
    include
)
target_link_libraries(${NAME} PRIVATE
    pico_stdlib
    hardware_pwm
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(${NAME})