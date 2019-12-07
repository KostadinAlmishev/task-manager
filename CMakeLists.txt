cmake_minimum_required(VERSION 3.15)
project(TaskManager CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#set(DATABASE_SOURCE_PACKAGE source/database)
#set(MANAGERS_SOURCE_PACKAGE source/managers)
#set(ENTITY_SOURCE_PACKAGE source/entity)
#set(TRACKING_SOURCE_PACKAGE source/tracking)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)
#include_directories(source)

file(GLOB_RECURSE TEST_SOURCE_FILES "test/*.cpp")
file(GLOB_RECURSE LIB_SOURCE_FILES "source/*.cpp")
#file(GLOB_RECURSE LIB_SOURCE_FILES
#        "${DATABASE_SOURCE_PACKAGE}/*/*.cpp"
#        "${DATABASE_SOURCE_PACKAGE}/commands/user/*.cpp"
#        "${MANAGERS_SOURCE_PACKAGE}/*.cpp"
#        "${ENTITY_SOURCE_PACKAGE}/*.cpp"
#        "${TRACKING_SOURCE_PACKAGE}/*.cpp")

add_library(TaskManagerLib STATIC ${LIB_SOURCE_FILES})

add_executable(TaskManager example/main.cpp)
add_executable(TaskManagerTest ${TEST_SOURCE_FILES})

set_target_properties(TaskManagerLib PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(TaskManagerTest PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(TaskManager TaskManagerLib)
target_link_libraries(TaskManagerTest TaskManagerLib)
target_link_libraries(TaskManagerTest ${GTEST_LIBRARIES})

#enable_testing()
