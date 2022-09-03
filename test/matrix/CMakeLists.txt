set(MATRIX_TEST matrix_test)

add_executable(${MATRIX_TEST} 
	matrix_test.cpp
	matrix_allocation_test.cpp
	matrix_fill_pixel_test.cpp
	matrix_vertical_draw_test.cpp 
	matrix_write_rgb565_pixel_rgb_test.cpp
	${PROJECT_FILES})

target_link_libraries(${MATRIX_TEST} GTest::gtest GTest::gtest_main)

gtest_discover_tests(${MATRIX_TEST})