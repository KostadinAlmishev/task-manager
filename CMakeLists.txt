cmake_minimum_required(VERSION 3.13)
project(TaskManager)

set(CMAKE_CXX_STANDARD 14)


include_directories(include)

file(GLOB_RECURSE CPPS
        source/*.cpp
        source/*/*.cpp
        )
#file(GLOB_RECURSE TEST_CPPS "test/*.cpp")


add_executable(${PROJECT_NAME}
        ${CPPS} main.cpp
        )
#add_executable(${PROJECT_NAME}  ${CPPS} test/test.cpp ${TEST_CPPS})


add_subdirectory(googletest)
#include googletest/include dir
include_directories(googletest/googletest/include)

#include the googlemock/include dir
include_directories(googletest/googlemock/include)


#Link with GoogleTest
target_link_libraries(TaskManager gtest gtest_main)

#Link with GoogleMock
target_link_libraries(TaskManager gmock gmock_main)

