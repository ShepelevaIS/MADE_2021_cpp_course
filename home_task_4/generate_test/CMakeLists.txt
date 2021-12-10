cmake_minimum_required(VERSION 3.0.0)

project(generate_test)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES *.cc)

message("PROJECT_NAME = ${PROJECT_NAME}")
message("SOURCES = ${SOURCES}")

add_executable(${PROJECT_NAME} ${SOURCES})