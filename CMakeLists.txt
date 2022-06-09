cmake_minimum_required(VERSION 3.0.0)

project(matrix VERSION 0.1.0)

include_directories( "include" )

file( GLOB SOURCES "src/*.c" "include/*.h" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

add_executable(matrix ${SOURCES})

IF (NOT WIN32)
  target_link_libraries(MY_EXECUTABLE m)
ENDIF()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
