cmake_minimum_required(VERSION 3.0.0)
project(matrix_calculator)

add_subdirectory(matrix_calculator_lib)

message("CALCULATOR_LIB_INCLUDE_DIRS = ${CALCULATOR_LIB_INCLUDE_DIRS}")
message("CALCULATOR_LIB_LIBRARIES = ${CALCULATOR_LIB_LIBRARIES}")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wpedantic -Wextra -Werror")

add_executable(${PROJECT_NAME} main.cc)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} INTERFACE ${CALCULATOR_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE ${CALCULATOR_LIB_LIBRARIES})

add_subdirectory(tests)
