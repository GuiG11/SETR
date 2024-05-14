cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(NCS)

target_sources(app PRIVATE app/main.c src-gen/VendingMachine.c)
target_include_directories(app PRIVATE src-gen src)
