cmake_minimum_required(VERSION 3.0.0)

project(matrix VERSION 0.1.0)

include_directories( "include" )

file( GLOB SOURCES "src/*.c" "include/*.h" )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")

# set(CMAKE_C_CPPLINT "cpplint")

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

add_executable(matrix ${SOURCES})

IF (NOT WIN32)
  target_link_libraries(matrix m)
ENDIF()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
