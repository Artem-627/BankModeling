cmake_minimum_required(VERSION 3.26.4)
project(BankModeling-tests)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

set(TESTS
        TimeTest.cpp
        WeekDay.cpp
)

add_executable(${PROJECT_NAME}
        main.cpp
        ${TESTS}

        ../include/Time.h
        ../source/Time.cpp
)
target_link_libraries(${PROJECT_NAME}
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})