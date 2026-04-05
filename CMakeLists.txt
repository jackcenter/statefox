cmake_minimum_required(VERSION 3.10)

project(StateFox C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_DOXYGEN "Build doxygen" ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(statefox
    src/sf_status.c
    src/statefox.c
)

target_include_directories(statefox PUBLIC include)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(statefox PRIVATE
        -Wall -Wextra -Wpedantic -Werror
        -Wconversion -Wsign-conversion -Wshadow -Wunused -Wundef -Wfloat-equal
    )
endif()

add_executable(simple_fsm examples/simple_fsm.c)
target_link_libraries(simple_fsm PRIVATE statefox)

enable_testing()

add_executable(test_statefox tests/test_statefox.c)
target_link_libraries(test_statefox PRIVATE statefox)
add_test(NAME test_statefox COMMAND test_statefox)

if (BUILD_DOXYGEN)
    add_subdirectory(docs)
endif()
