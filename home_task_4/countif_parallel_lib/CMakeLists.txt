cmake_minimum_required(VERSION 3.0.0)
project(countif_parallel_lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wpedantic -Wextra -Werror")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(COUNTIF_PARALLEL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)