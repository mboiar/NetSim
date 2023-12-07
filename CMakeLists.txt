cmake_minimum_required(VERSION 3.13)
project(implementation)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_TESTS ON)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
)

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
        message(STATUS "GCC detected, adding compile flags")
        add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion -Wno-error=pessimizing-move)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
        add_compile_options(/Z7 /W4 /wd4146 /wd4245 /RTCcsu)
endif(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
add_executable(main ${SOURCE_FILES} main.cpp)

if ((DEFINED BUILD_TESTS) AND (BUILD_TESTS STREQUAL "ON"))
        include(FetchContent)
        FetchContent_Declare(
                googletest
                URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        )
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
        enable_testing()

        target_compile_definitions(main PUBLIC EXERCISE_ID=EXERCISE_ID_PACKAGES)

        set(SOURCES_FILES_TESTS
                #            test/test_Factory.cpp
                #            test/test_factory_io.cpp
                #            test/test_nodes.cpp
                test/test_package.cpp
                #            test/test_reports.cpp
                #            test/test_simulate.cpp
                test/test_storage_types.cpp
        )
        set( TEST_SRC
                src/package.cpp
                src/storage_types.cpp
        )
        set(EXEC_TEST main__test)
        add_executable(${EXEC_TEST} ${TEST_SRC} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)
        target_link_libraries(${EXEC_TEST} PRIVATE GTest::gtest_main GTest::gmock_main)
        include(GoogleTest)
        gtest_discover_tests(${EXEC_TEST})
endif()