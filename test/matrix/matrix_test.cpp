#include "gtest/gtest.h"
#include "matrix.h"

/**
 * @brief Validate that if passed a zero-zero dimension sized
 * matrix, that no matrix will be allocated.
 */
TEST(MatrixSetupSuite, ValidateZeroZeroMatrix)
{
    matrix *mat = allocate_matrix(0, 0);

    ASSERT_EQ(mat, nullptr);
}

/**
 * @brief Validate that one-one dimension sized matrix
 * allocates with no issue.
 */
TEST(MatrixSetupSuite, ValidateOneOneMatrix)
{
    matrix* mat = allocate_matrix(1, 1);

    ASSERT_NE(mat, nullptr);
}

/**
 * @brief Validate that for any newly allocated matrix,
 * the values in the matrix are equal to 0.
 */
TEST(MatrixSetupSuite, ValidateMatrixIsZerod)
{
    uint16_t horizontal_dim = 10;
    uint16_t vertical_dim = 10;

    matrix *mat = allocate_matrix(horizontal_dim, vertical_dim);

    for(uint32_t index = 0; index < (horizontal_dim * vertical_dim); ++index) {
        ASSERT_EQ(mat->mem[index], 0x0000);
    }
}

/**
 * @brief Validate that the underlying matrix memory allocated
 * is equal to (N x M)
 */
TEST(MatrixSetupSuite, ValidateMatrixMemorySize)
{
    uint16_t horizontal_dim = 10;
    uint16_t vertical_dim = 10;

    matrix *mat = allocate_matrix(horizontal_dim, vertical_dim);

    ASSERT_EQ(mat->size, (horizontal_dim * vertical_dim));
}

/**
 * @brief Any attempts to deallocate a NULL matrix must
 * result in Invalid return enum.
 */
TEST(MatrixSetupSuite, DeallocateInvalidMatrix)
{
    mat_fn_status status = deallocate_matrix(NULL);

    ASSERT_EQ(status, NULL_MAT);
}

/**
 * @brief An allocated matrix should be deallocated
 * without any issues. A valid enum value should be returned.
 */
TEST(MatrixSetupSuite, DeallocateValidMatrix)
{
    matrix *mat = allocate_matrix(1, 1);

    ASSERT_NE(mat, nullptr);

    mat_fn_status status = deallocate_matrix(mat);

    ASSERT_EQ(status, VALID_OP);
}

// Reference: https://www.sandordargo.com/blog/2019/04/24/parameterized-testing-with-gtest
class WriteRGB565RGBDimensionTestFixture : public testing::TestWithParam<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, mat_fn_status>>  {
};

#define HORIZONTAL_DIM 10
#define VERTICAL_DIM 10

matrix *allocate_dummy_matrix()
{
    return allocate_matrix(HORIZONTAL_DIM, VERTICAL_DIM);
}

/**
 * @brief Parameterized method that validates that write_rgb565_pixel_rbg()
 * will return the appropriate enum value depending on col, row input values.
 */
TEST_P(WriteRGB565RGBDimensionTestFixture, ValidateDimensionRestriction) 
{
    uint8_t red = std::get<0>(GetParam());
    uint8_t green = std::get<1>(GetParam());
    uint8_t blue = std::get<2>(GetParam());
    uint16_t row = std::get<3>(GetParam());
    uint16_t col = std::get<4>(GetParam());
    mat_fn_status expected_status = std::get<5>(GetParam());

    std::cout << "\tParameters: \n";
    std::cout << "\tred: 0x" << std::hex << static_cast<uint16_t>(red) << std::endl;
    std::cout << "\tgreen: 0x" << std::hex << static_cast<uint16_t>(green) << std::endl;
    std::cout << "\tblue: 0x" << std::hex << static_cast<uint16_t>(blue) << std::endl;
    std::cout << "\trow: " << std::hex << row << std::endl;
    std::cout << "\tcol: " << std::to_string(col) << std::endl;
    std::cout << "\texpected stat: " << expected_status << "\n";

    matrix* mat = allocate_dummy_matrix();

    mat_fn_status status = write_rgb565_pixel_rgb(mat, red, green, blue, row, col);

    ASSERT_EQ(status, expected_status);

    status = deallocate_matrix(mat);

    ASSERT_EQ(status, VALID_OP);
}

INSTANTIATE_TEST_CASE_P(WriteToInvalidDimensions, WriteRGB565RGBDimensionTestFixture, testing::Values(
    std::make_tuple(0x00, 0x00, 0x00, 11, 0x00, INVALID_PARAM),  
    std::make_tuple(0x00, 0x00, 0x00, 10, 0x00, INVALID_PARAM),
    std::make_tuple(0x00, 0x00, 0x00,  9, 0x00, VALID_OP),
    std::make_tuple(0x00, 0x00, 0x00, -1, 0x00, INVALID_PARAM),
    std::make_tuple(0x00, 0x00, 0x00, 0x00, 11, INVALID_PARAM),
    std::make_tuple(0x00, 0x00, 0x00, 0x00, 10, INVALID_PARAM),
    std::make_tuple(0x00, 0x00, 0x00, 0x00,  9, VALID_OP),
    std::make_tuple(0x00, 0x00, 0x00, 0x00, -1, INVALID_PARAM)
));


TEST(RBG565RGBWrite, WriteRGBToInvalidMatrix) 
{
    matrix* mat = nullptr;

    mat_fn_status status = write_rgb565_pixel_rgb(mat, 0xFF, 0xFF, 0xFF, 1, 1);

    ASSERT_EQ(status, NULL_MAT);
}


class WriteRgb565RGBPixelValueTestFixture : public testing::TestWithParam<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, uint16_t>>  {
};

/**
 * @brief Parameterized method that will validate that the value
 * written at a specific (row,col) position equals the expected value.
 */
TEST_P(WriteRgb565RGBPixelValueTestFixture, ValidatePixelValue)
{
    uint8_t red = std::get<0>(GetParam());
    uint8_t green = std::get<1>(GetParam());
    uint8_t blue = std::get<2>(GetParam());
    uint16_t row = std::get<3>(GetParam());
    uint16_t col = std::get<4>(GetParam());
    uint16_t true_color = std::get<5>(GetParam());;

    std::cout << "\tParameters: \n";
    std::cout << "\tred: 0x" << std::hex << static_cast<uint16_t>(red) << std::endl;
    std::cout << "\tgreen: 0x" << std::hex << static_cast<uint16_t>(green) << std::endl;
    std::cout << "\tblue: 0x" << std::hex << static_cast<uint16_t>(blue) << std::endl;
    std::cout << "\trow: " << std::hex << row << std::endl;
    std::cout << "\tcol: " << std::to_string(col) << std::endl;
    std::cout << "\ttrue color: " << std::hex << true_color << std::endl;

    matrix* mat = allocate_dummy_matrix();

    mat_fn_status status = write_rgb565_pixel_rgb(mat, red, green, blue, row, col);

    ASSERT_EQ(status, VALID_OP);

    uint32_t position = calculate_offset(mat, row, col);

    std::cout << "\tMatrix position pixel value: 0x" << std::hex << mat->mem[position] << std::endl;

    ASSERT_EQ(mat->mem[position], true_color);
}

INSTANTIATE_TEST_CASE_P(WriteRGB565PixelValue, WriteRgb565RGBPixelValueTestFixture, testing::Values(
    std::make_tuple(0x00, 0x00, 0x00, 5, 5, 0x0000),
    std::make_tuple(0xFF, 0xFF, 0xFF, 5, 5, 0xFFFF),
    std::make_tuple(0xFF, 0x00, 0x00, 5, 5, 0xF800),
    std::make_tuple(0x00, 0xFF, 0x00, 5, 5, 0x07E0),
    std::make_tuple(0x00, 0x00, 0xFF, 5, 5, 0x001F)
));

class FillPixelValidateInputsTextFixture : public testing::TestWithParam<std::tuple<matrix*, uint8_t, uint8_t, uint8_t, mat_fn_status, mat_fn_status>> {
};

TEST_P(FillPixelValidateInputsTextFixture, ValidateFillPixelInputs) {
    matrix* mat = std::get<0>(GetParam());
    uint8_t pt_size = std::get<1>(GetParam());
    uint8_t row = std::get<2>(GetParam());
    uint8_t col = std::get<3>(GetParam());
    mat_fn_status expected_status = std::get<4>(GetParam());
    mat_fn_status expected_deallocation_status = std::get<5>(GetParam());

    std::cout << "\tParameters: \n";
    std::cout << "\tpoint size: " << pt_size << std::endl;
    std::cout << "\trow: " << std::hex << row << std::endl;
    std::cout << "\tcol: " << std::to_string(col) << std::endl;
    std::cout << "\texpected status: " << expected_status << std::endl;
    std::cout << "\texpected deallocation status: " << expected_deallocation_status << std::endl;

    mat_fn_status stat = fill_pixel(mat, 0xFFFF, pt_size, row, col);

    ASSERT_EQ(stat, expected_status);

    stat = deallocate_matrix(mat);

    ASSERT_EQ(stat, expected_deallocation_status);
}

INSTANTIATE_TEST_CASE_P(FillPixelInputValues, FillPixelValidateInputsTextFixture, testing::Values(
    std::make_tuple(nullptr, 1, 1, 1, NULL_MAT, NULL_MAT),
    std::make_tuple(allocate_dummy_matrix(), 1, 100, 1, NULL_MAT, NULL_MAT),
    std::make_tuple(allocate_dummy_matrix(), 1, 1, 100, INVALID_PARAM, VALID_OP),
    std::make_tuple(allocate_dummy_matrix(), 1, 100, 100, INVALID_PARAM, VALID_OP),
    std::make_tuple(allocate_dummy_matrix(), 0, 1, 1, INVALID_PARAM, VALID_OP),
    std::make_tuple(allocate_dummy_matrix(), 1, 1, 1, VALID_OP, VALID_OP),
    std::make_tuple(allocate_dummy_matrix(), 100, 1, 1, VALID_OP, VALID_OP)
));

// Vertical line verification is a very interesting to test.
//  -> Likely we need to do bounds checking first.
//  -> Then we will need to do sample manual verification that
//      the data written out is what we expect it to be.    

TEST(DrawVerticalLine, sample) 
{
    matrix* mat = allocate_dummy_matrix();

    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t col = 5;
    uint16_t start_row = 1;
    uint16_t end_row = 4;
}

int main(int argc, char* argv[]) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}