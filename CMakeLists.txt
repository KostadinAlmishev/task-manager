cmake_minimum_required(VERSION 3.12)
project(task_manager)

set(CMAKE_CXX_STANDARD 17)

#set(${INCLUDES_DIR} ${PROJECT_SOURCE_DIR}/includes)


include_directories(${PROJECT_SOURCE_DIR}/includes)


file(GLOB
        CPPS "src/*.cpp")

#add_executable(${PROJECT_NAME} main.cpp ${CPPS})
add_executable(${PROJECT_NAME} test/test.cpp ${CPPS})



add_subdirectory(googletest)

#include googletest/include dir
include_directories(googletest/googletest/include)

#include the googlemock/include dir
include_directories(googletest/googlemock/include)

#Link with GoogleTest
target_link_libraries(task_manager gtest gtest_main)

#Link with GoogleMock
target_link_libraries(task_manager gmock gmock_main)

