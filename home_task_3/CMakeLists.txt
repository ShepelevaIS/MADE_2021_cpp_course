cmake_minimum_required(VERSION 3.0.0)
project(set)

add_subdirectory(set_lib)

set(CMAKE_CXX_STANDARD 17)
message("SET_LIB_INCLUDE_DIRS = ${SET_LIB_INCLUDE_DIRS}")
message("SET_LIB_LIBRARIES = ${SET_LIB_LIBRARIES}")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wpedantic -Wextra -Werror")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++17")

add_executable(${PROJECT_NAME} main.cc)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} INTERFACE ${SET_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE ${SET_LIB_LIBRARIES})

add_subdirectory(tests)
