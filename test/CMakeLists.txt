# cmake_minimum_required(VERSION 3.0.0)

# project(TEST_matrix VERSION 0.1.0)

# include_directories( "../include" )

# file( GLOB SOURCES "*.cpp" "*.hpp" "../src/bitmap.c" "../src/matrix.c" "../include/*.h" )
# # file( GLOB SOURCES "*.cpp" )

# message(STATUS "foo include dir: ${SOURCES}")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

# find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
# if (CMAKE_CXX_CPPCHECK)
#     list(
#         APPEND CMAKE_CXX_CPPCHECK 
#             "--enable=warning"
#             "--inconclusive"
#             "--force" 
#             "--inline-suppr"
#             # "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
#     )
# endif()

# find_package(GTest REQUIRED)

# add_executable(TEST_matrix ${SOURCES})

# target_link_libraries( TEST_matrix PRIVATE GTest::GTest GTest::Main m )

find_package(GTest REQUIRED)
include(GoogleTest)

if(TEST_MATRIX)
    add_subdirectory(matrix)
endif()