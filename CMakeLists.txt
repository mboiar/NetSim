cmake_minimum_required(VERSION 3.13)
project(implementation)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        )

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
        message(STATUS "GCC detected, adding compile flags")
        add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
        add_compile_options(/Z7 /W4 /wd4146 /wd4245 /RTCcsu)
endif(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
add_executable(main ${SOURCE_FILES} main.cpp)