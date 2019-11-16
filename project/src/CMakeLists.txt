cmake_minimum_required(VERSION 3.15)
project(GUI)

add_library(${PROJECT_NAME} STATIC Parser.cpp)
add_library(code::gui ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES_DIR})