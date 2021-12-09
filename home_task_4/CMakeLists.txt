cmake_minimum_required(VERSION 3.0.0)

project(countif)

set(CMAKE_CXX_STANDARD 20)

option(USE_SEQUENTIAL "Use sequential lib" OFF)
if(USE_SEQUENTIAL)
    add_subdirectory(countif_sequential_lib)

    message("COUNTIF_SEQUENTIAL_LIB_LIBRARIES = ${COUNTIF_SEQUENTIAL_LIB_LIBRARIES}")
    message("PROJECT_NAME = ${PROJECT_NAME}")

    add_library(${PROJECT_NAME}sequential STATIC ${COUNTIF_SEQUENTIAL_LIB_LIBRARIES}/countif_sequential.cc) 
    add_executable(${PROJECT_NAME}_sequential main.cc)
    target_include_directories(${PROJECT_NAME}_sequential PUBLIC ${PROJECT_NAME}_lib)
    target_link_libraries(${PROJECT_NAME}_sequential PUBLIC ${PROJECT_NAME}sequential)
else()
    add_subdirectory(countif_parallel_lib)

    message("COUNTIF_PARALLEL_LIB_LIBRARIES = ${COUNTIF_PARALLEL_LIB_LIBRARIES}")
    message("PROJECT_NAME = ${PROJECT_NAME}")

    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
    add_library(${PROJECT_NAME}parallel SHARED ${COUNTIF_PARALLEL_LIB_LIBRARIES}/countif_parallel.cc) 
    add_executable(${PROJECT_NAME}_parallel main.cc)
    target_include_directories(${PROJECT_NAME}_parallel PUBLIC ${PROJECT_NAME}_lib)
    target_link_libraries(${PROJECT_NAME}_parallel PUBLIC ${PROJECT_NAME}parallel)
endif(USE_SEQUENTIAL)

# add_subdirectory(tests)