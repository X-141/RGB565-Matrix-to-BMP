cmake_minimum_required(VERSION 3.0.0)

project(matrix VERSION 0.1.0)

include_directories( "include" )

file( GLOB SOURCES "src/*.c" "include/*.h" )

add_executable(matrix ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
