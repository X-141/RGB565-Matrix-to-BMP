find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

option(TEST_MATRIX "Build test executable for Matrix library." OFF)
option(TEST_BITMAP "Build test executable for Bitmap library." OFF)

if(TEST_MATRIX)
    add_subdirectory(matrix)
endif()