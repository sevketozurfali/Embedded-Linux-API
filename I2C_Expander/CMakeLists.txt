cmake_minimum_required(VERSION 3.17)
project(I2C_Expander C)

set(CMAKE_C_STANDARD 99)

add_executable(I2C_Expander main.c libs/max7321.c libs/max7321.h)