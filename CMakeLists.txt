cmake_minimum_required(VERSION 3.2)

project(Sudoku-Solver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main)

add_compile_options(main PRIVATE
    -Wall -Wextra -Werror -Weffc++ -Wconversion -Wsign-conversion -Wpedantic -ggdb -DNDEBUG
)

target_sources(main PRIVATE
    src/main.cpp
    src/Sudoku.cpp
    src/AlgorithmX.cpp
)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
if (${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/clang")
    target_link_libraries(main PRIVATE c++)
endif()