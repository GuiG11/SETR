cmake_minimum_required(VERSION 3.10)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(IoT)

target_sources(app PRIVATE src/IoT.c src/RTDB.h src/RTDB.c)
target_include_directories(app PRIVATE src)
