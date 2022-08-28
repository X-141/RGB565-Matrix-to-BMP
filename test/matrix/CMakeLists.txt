include_directories("../../include")

set(MATRIX_TEST matrix_test)

message(STATUS "foo include dir: ${SOURCES}")

find_package(GTest CONFIG REQUIRED)

add_executable(${MATRIX_TEST} matrix_test.cpp "../../src/bitmap.c" "../../src/matrix.c" )
target_link_libraries(${MATRIX_TEST} GTest::gtest GTest::gtest_main)

gtest_discover_tests(${MATRIX_TEST})