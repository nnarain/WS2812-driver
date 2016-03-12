
cmake_minimum_required(VERSION 2.8)

set(AVR_MCU "atmega328p")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/avr-gcc.toolchain.cmake")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(WS2812 C CXX ASM)

add_definitions(-DF_CPU=16000000)

add_subdirectory(test)