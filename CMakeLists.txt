cmake_minimum_required(VERSION 3.10)
project(StateFox C)

# -------------------------
# Build options
# -------------------------
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# -------------------------
# Include directories
# -------------------------
include_directories(${PROJECT_SOURCE_DIR}/include)

# -------------------------
# Core library
# -------------------------
add_library(statefox
    src/statefox.c
)

target_include_directories(statefox PUBLIC include)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(statefox PRIVATE
        -Wall -Wextra -Wpedantic -Werror
        -Wconversion -Wsign-conversion -Wshadow -Wunused -Wundef -Wfloat-equal
    )
endif()

# -------------------------
# Examples
# -------------------------
add_executable(simple_fsm examples/simple_fsm.c)
target_link_libraries(simple_fsm PRIVATE statefox)

# -------------------------
# Tests
# -------------------------
enable_testing()

add_executable(test_statefox tests/test_statefox.c)
target_link_libraries(test_statefox PRIVATE statefox)
add_test(NAME test_statefox COMMAND test_statefox)
