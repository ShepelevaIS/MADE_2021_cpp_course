cmake_minimum_required(VERSION 3.0.0)
project(matrix_calculator)

add_subdirectory(matrix_calculator_lib)

set(CMAKE_CXX_STANDARD 17)
message("CALCULATOR_LIB_INCLUDE_DIRS = ${CALCULATOR_LIB_INCLUDE_DIRS}")
message("CALCULATOR_LIB_LIBRARIES = ${CALCULATOR_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cc)

target_include_directories(${PROJECT_NAME} PUBLIC ${CALCULATOR_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CALCULATOR_LIB_LIBRARIES})

add_subdirectory(tests)
