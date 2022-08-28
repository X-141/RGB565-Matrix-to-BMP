find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

if(TEST_MATRIX)
    add_subdirectory(matrix)
endif()