cmake_minimum_required(VERSION 3.13)
project(implementation)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        )

add_compile_options(-Wall -Wextra -Wpedantic -pedantic-errors -Wconversion)
add_executable(main ${SOURCE_FILES} main.cpp)