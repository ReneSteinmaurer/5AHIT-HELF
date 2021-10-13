cmake_minimum_required(VERSION 3.13.4)
project(01_test C)

set(CMAKE_C_STANDARD 99)

add_executable(01_test main.c lcd_i2c.c)

target_link_libraries(01_test wiringPi)