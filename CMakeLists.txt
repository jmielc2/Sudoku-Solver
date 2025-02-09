cmake_minimum_required(VERSION 3.5)

project(Sudoku-Solver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main)

add_compile_options(
    -Wall -Wextra -Werror -Wshadow -Wnon-virtual-dtor -Wpedantic -Weffc++
    -Wold-style-cast -Wconversion -Wsign-conversion -Wlifetime -Wformat=2
    -Wcast-align -Woverloaded-virtual -Wnull-dereference -Wdouble-promotion
    -Wunused-variable
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-ggdb)
else()
    add_compile_options(-O3 -DNDEBUG)
endif()

target_sources(main PRIVATE
    src/main.cpp
    src/util.cpp
)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)
if (${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/clang")
    target_link_libraries(main PRIVATE c++)
endif()