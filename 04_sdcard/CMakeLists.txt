cmake_minimum_required(VERSION 3.16)
project(04_sdcard C)

set(CMAKE_C_STANDARD 99)

add_executable(04_sdcard main.c)

target_link_libraries(04_sdcard wiringPi)