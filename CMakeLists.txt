cmake_minimum_required(VERSION 3.15)
project(task_manager)

set(CMAKE_CXX_STANDARD 17)


include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE
        CPPS "source/*.cpp")
file(GLOB_RECURSE
        TEST_CPPS "test/*.cpp")

add_executable(${PROJECT_NAME}  ${CPPS} test/test.cpp ${TEST_CPPS})


add_subdirectory(googletest)
#include googletest/include dir
include_directories(googletest/googletest/include)

#include the googlemock/include dir
include_directories(googletest/googlemock/include)

#Link with GoogleTest
target_link_libraries(task_manager gtest gtest_main)

#Link with GoogleMock
target_link_libraries(task_manager gmock gmock_main)

