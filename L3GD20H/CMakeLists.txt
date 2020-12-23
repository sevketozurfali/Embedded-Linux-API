cmake_minimum_required(VERSION 3.17)
project(L3GD20H C)

set(CMAKE_C_STANDARD 99)

add_executable(L3GD20H main.c L3GD20H.c L3GD20H.h examples/temperature_measure.c)