cmake_minimum_required(VERSION 3.15)
project(RVM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(RVM
    mainvm.c
    memory/mainmem.c
    cpu/cpu.c
    bootstrap.c
)

target_include_directories(RVM PRIVATE $(PROJECT_SOURCE_DIR)/memory)
target_include_directories(RVM PRIVATE $(PROJECT_SOURCE_DIR)/cpu)

