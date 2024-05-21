cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(IoT)

target_sources(app PRIVATE src/IoT.c)
target_include_directories(app PRIVATE src)