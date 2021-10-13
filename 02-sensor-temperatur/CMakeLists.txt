# cmake_minimum_required(VERSION <specify CMake version here>)
project(02_sensor_auslesen C)

set(CMAKE_C_STANDARD 99)

add_executable(02-sensor-auslesen main.c lcd_i2c.c)

target_link_libraries(02-sensor-auslesen wiringPi)
