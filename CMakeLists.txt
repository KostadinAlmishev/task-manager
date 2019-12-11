cmake_minimum_required(VERSION 3.15)
project(task_manager)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(googletest/googletest/include)
include_directories(cmake-build-debug)

include_directories(
        include/.
        test/
)


file( GLOB_RECURSE SOURCE_FILES
        source/*/*.cpp
        source/*.cpp
        test/*/*.cpp
        )
add_executable(
        ${PROJECT_NAME}
        ${SOURCE_FILES}
        test/main.cpp
)

add_subdirectory(googletest)

#include googletest/include dir
include_directories(googletest/googletest/include)

#include the googlemock/include dir
include_directories(googletest/googlemock/include)

#Link with GoogleTest
target_link_libraries(task_manager gtest gtest_main)

#Link with GoogleMock
target_link_libraries(task_manager gmock gmock_main)