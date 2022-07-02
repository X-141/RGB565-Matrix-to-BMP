cmake_minimum_required(VERSION 3.0.0)

project(matrix VERSION 0.1.0)

include_directories( "include" )

file( GLOB SOURCES "src/*.c" "include/*.h" )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")

find_program(CMAKE_C_CPPCHECK NAMES cppcheck)
if (CMAKE_C_CPPCHECK)
    list(
        APPEND CMAKE_C_CPPCHECK 
            "--enable=warning"
            "--inconclusive"
            "--force" 
            "--inline-suppr"
            # "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
    )
endif()

option(TEST_MATRIX "Build test executable for Matrix library." ON)
option(TEST_BITMAP "Build test executable for Bitmap library." ON)

add_executable(matrix ${SOURCES})

IF (NOT WIN32)
  target_link_libraries(matrix m)
ENDIF()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

add_subdirectory("test")
