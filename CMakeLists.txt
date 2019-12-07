cmake_minimum_required(VERSION 3.15)
project(task_manager)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILES
        source/*/*.cpp
        source/*.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} tests/main.cpp)

