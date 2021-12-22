cmake_minimum_required(VERSION 3.0.0)
project(specialists_db)

add_subdirectory(specialists_db_lib)

message("SPECIALISTS_DB_LIB_INCLUDE_DIRS = ${SPECIALISTS_DB_LIB_INCLUDE_DIRS}")
message("SPECIALISTS_DB_LIB_LIBRARIES = ${SPECIALISTS_DB_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${SPECIALISTS_DB_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SPECIALISTS_DB_LIB_LIBRARIES})

add_subdirectory(tests)
