cmake_minimum_required(VERSION 3.16)
project(03-sensor-licht C)

set(CMAKE_C_STANDARD 99)

add_executable(03-sensor-licht main.c lcd_i2c.c)

target_link_libraries(03-sensor-licht wiringPi)