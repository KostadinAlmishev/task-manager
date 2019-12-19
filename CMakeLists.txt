cmake_minimum_required(VERSION 3.15)
project(TaskManager CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(GTest REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(Boost REQUIRED)
find_package(CURL REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PostgreSQL_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(include)
include_directories(example/include)

file(GLOB_RECURSE LIB_SOURCE_FILES "source/*.cpp")
file(GLOB_RECURSE EX_SOURCE_FILES "example/source/*.cpp")
file(GLOB_RECURSE TEST_SOURCE_FILES "test/*.cpp")

add_library(TaskManagerLib STATIC ${LIB_SOURCE_FILES})
add_library(TaskManagerEx STATIC ${EX_SOURCE_FILES})

add_executable(TaskManager example/main.cpp)
add_executable(TaskManagerTest ${TEST_SOURCE_FILES})

set_target_properties(TaskManagerLib PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(TaskManagerEx PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(TaskManagerTest PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(TaskManager TaskManagerEx)
target_link_libraries(TaskManager TaskManagerLib)
target_link_libraries(TaskManager ${PostgreSQL_LIBRARIES})
target_link_libraries(TaskManager ${Boost_LIBRARIES})
target_link_libraries(TaskManager ${CURL_LIBRARIES})

target_link_libraries(TaskManagerTest TaskManagerLib)
target_link_libraries(TaskManagerTest ${GTEST_LIBRARIES})

#enable_testing()
