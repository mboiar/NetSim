cmake_minimum_required(VERSION 3.13)
project(implementation)

set(CMAKE_CXX_STANDARD 17)

# turn tests compilation on/off
set(BUILD_TESTS ON)

# edit extra compilation flags
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(
        include
)

set(SOURCE_FILES

        )

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
#            test/test_package.cpp
#            test/test_reports.cpp
#            test/test_simulate.cpp
#            test/test_storage_types.cpp
            )
    set( TEST_SRC

            )
    set(EXEC_TEST main__test)
    add_executable(${EXEC_TEST} ${TEST_SRC} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)
    target_link_libraries(${EXEC_TEST} PRIVATE GTest::gtest_main GTest::gmock_main)
    include(GoogleTest)
    gtest_discover_tests(${EXEC_TEST})
endif()