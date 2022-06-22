#pragma once

#include "gtest/gtest.h"
#include "matrix.h"

TEST(TEST_MATRIX_SUITE, deallocate_invalid_matrix)
{
    mat_fn_status status = deallocate_matrix(NULL);

    ASSERT_EQ(status, INVALID_PARAM);
}

TEST(TEST_MATRIX_SUITE, deallocate_valid_matrix)
{
    matrix *mat = allocate_matrix(1, 1);

    ASSERT_NE(mat, nullptr);

    mat_fn_status status = deallocate_matrix(mat);

    ASSERT_EQ(status, VALID_OP);
}

// Reference: https://www.sandordargo.com/blog/2019/04/24/parameterized-testing-with-gtest
class WriteRgb565PixelTestFixture : public testing::TestWithParam<std::tuple<bool, uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, mat_fn_status>>  {
};

#define HORIZONTAL_DIM 10
#define VERTICAL_DIM 10

matrix *allocate_dummy_matrix()
{
    return allocate_matrix(HORIZONTAL_DIM, VERTICAL_DIM);
}

TEST_P(WriteRgb565PixelTestFixture, ValidatePixelWriteOutputs) {
    bool allocate_mat = std::get<0>(GetParam());
    uint8_t red = std::get<1>(GetParam());
    uint8_t green = std::get<2>(GetParam());
    uint8_t blue = std::get<3>(GetParam());
    uint16_t row = std::get<4>(GetParam());
    uint16_t col = std::get<5>(GetParam());
    mat_fn_status expected_status = std::get<6>(GetParam());

    std::cout << "Parameters: \n";
    std::cout << "\talloc_mat: " << allocate_mat << "\n";
    std::cout << "\tred: " << std::to_string(red) << "\n";
    std::cout << "\tgreen: " << std::to_string(green) << "\n";
    std::cout << "\tblue: " << std::to_string(blue) << "\n";
    std::cout << "\trow: " << std::to_string(row) << "\n";
    std::cout << "\tcol: " << std::to_string(col) << "\n";
    std::cout << "\texpected stat: " << expected_status << "\n";

    matrix* mat = nullptr;
    if(allocate_mat)
        mat = allocate_dummy_matrix();

    mat_fn_status status = write_rgb565_pixel_rgb(mat, red, green, blue, row, col);

    ASSERT_EQ(status, expected_status);
}

INSTANTIATE_TEST_CASE_P(write_rgb565_rgb, WriteRgb565PixelTestFixture, testing::Values(
    std::make_tuple(false, 0x00, 0x00, 0x00, 0x00, 0x00, INVALID_PARAM),
    std::make_tuple(true, 0x00, 0x00, 0x00, 11, 0x00, INVALID_PARAM),
    std::make_tuple(true, 0x00, 0x00, 0x00, 10, 0x00, INVALID_PARAM),
    std::make_tuple(true, 0x00, 0x00, 0x00, -1, 0x00, INVALID_PARAM),
    std::make_tuple(true, 0x00, 0x00, 0x00, 0x00, 11, INVALID_PARAM),
    std::make_tuple(true, 0x00, 0x00, 0x00, 0x00, 10, INVALID_PARAM),
    std::make_tuple(true, 0x00, 0x00, 0x00, 0x00, -1, INVALID_PARAM)
));

TEST(TEST_MATRIX_SUITE, write_rgb565_pixel_rgb_value)
{
}