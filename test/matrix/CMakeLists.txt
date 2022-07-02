include_directories("../../include")

message(STATUS "foo include dir: ${SOURCES}")

add_executable(matrix_test matrix_test.cpp "../../src/bitmap.c" "../../src/matrix.c" )
target_link_libraries(matrix_test GTest::GTest GTest::Main)

gtest_discover_tests(matrix_test)