cmake_minimum_required(VERSION 3.10)
project(MemoryManagement C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wno-unused-parameter -Wno-unused-variable -g -O0")

# Define source files
set(TEST_SOURCES check_mm.c mm.c memory_setup.c)
set(APP_SOURCES main.c io.c mm.c memory_setup.c)

# Define executables
add_executable(malloc_check ${TEST_SOURCES})
add_executable(cmd_int ${APP_SOURCES})

# Link libraries for the test executable
target_link_libraries(malloc_check check subunit m)