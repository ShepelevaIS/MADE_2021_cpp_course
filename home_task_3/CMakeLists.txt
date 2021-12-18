cmake_minimum_required(VERSION 3.0.0)
project(set)

add_subdirectory(set_lib)

set(CMAKE_CXX_STANDARD 17)
message("SET_LIB_INCLUDE_DIRS = ${SET_LIB_INCLUDE_DIRS}")
message("SET_LIB_LIBRARIES = ${SET_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cc)

target_include_directories(${PROJECT_NAME} INTERFACE ${SET_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE ${SET_LIB_LIBRARIES})

add_subdirectory(tests)
