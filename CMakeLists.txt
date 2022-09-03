cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME "RGB565")

project(${PROJECT_NAME} VERSION 0.1.0)

include_directories( "include" )

set(PROJECT_FILES 
  "${PROJECT_SOURCE_DIR}/src/bitmap.c" "${PROJECT_SOURCE_DIR}/include/bitmap.h"
  "${PROJECT_SOURCE_DIR}/src/matrix.c" "${PROJECT_SOURCE_DIR}/include/matrix.h"
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
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

option(BUILD_MAIN_EXECUTABLE "Build main executable" ON)

if(BUILD_MAIN_EXECUTABLE)
  set(MAIN_FILE "src/main.c")
  add_executable(${PROJECT_NAME} ${MAIN_FILE} ${PROJECT_FILES})
  if (NOT WIN32)
    target_link_libraries(matrix m)
  endif()
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

add_subdirectory("test")