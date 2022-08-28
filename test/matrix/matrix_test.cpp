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
class WriteRGB565RGBDimensionTestFixture : public testing::TestWithParam<std::tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, mat_fn_status>>  {
};

constexpr uint8_t HORIZONTAL_DIM = 10;
constexpr uint8_t  VERTICAL_DIM = 10;

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
    std::string testCaseTitle;
    uint8_t red, green, blue;
    uint16_t row, col;
    mat_fn_status expected_status;
    std::tie(testCaseTitle, red, green, blue, row, col, expected_status) = GetParam();
    //const auto [testCaseTitle, red, green, blue, row, col] = GetParam();

    std::cout << "Test Case: " << testCaseTitle << std::endl;
    std::cout << "\tParameters: \n";
    std::cout << "\t\tred: 0x" << std::hex << static_cast<uint16_t>(red) << std::endl;
    std::cout << "\t\tgreen: 0x" << std::hex << static_cast<uint16_t>(green) << std::endl;
    std::cout << "\t\tblue: 0x" << std::hex << static_cast<uint16_t>(blue) << std::endl;
    std::cout << "\t\trow: " << std::hex << row << std::endl;
    std::cout << "\t\tcol: " << std::to_string(col) << std::endl;
    std::cout << "\t\texpected stat: " << expected_status << "\n";

    matrix* mat = allocate_dummy_matrix();

    mat_fn_status status = write_rgb565_pixel_rgb(mat, red, green, blue, row, col);

    std::cout << "result stat: " << status << "\n";

    ASSERT_EQ(status, expected_status);

    status = deallocate_matrix(mat);

    ASSERT_EQ(status, VALID_OP);
}


INSTANTIATE_TEST_SUITE_P(WriteToInvalidDimensions, WriteRGB565RGBDimensionTestFixture, testing::Values(
    std::make_tuple("Accessing Invalid Row Dimension (Vertical Dim + 1) ", 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), 0, INVALID_PARAM),
    std::make_tuple("Accessomg Invalid Row Dimension (Vertical Dim + 0)", 0x00, 0x00, 0x00, (VERTICAL_DIM), 0x00, INVALID_PARAM),
    std::make_tuple("Accessing Valid Row Dimension (Vertical Dim - 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), 0x00, VALID_OP),
    std::make_tuple("Accessing Invalid Row Dimension (Negative Value)", 0x00, 0x00, 0x00, -1, 0x00, INVALID_PARAM),
    std::make_tuple("Accessing Invalid Column Dimension (Horizontal Dim + 1)", 0x00, 0x00, 0x00, 0x00, (HORIZONTAL_DIM + 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Column Dimension (Horizontal Dim + 0)", 0x00, 0x00, 0x00, 0x00, (HORIZONTAL_DIM), INVALID_PARAM),
    std::make_tuple("Accessing Valid Column Dimension (Horizontal Dim - 1)", 0x00, 0x00, 0x00, 0x00, (HORIZONTAL_DIM - 1), VALID_OP),
    std::make_tuple("Accessing Invalid Column Dimension (Negative Value)", 0x00, 0x00, 0x00, 0x00, -1, INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 0)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM),
    std::make_tuple("Accessing Valid Row and Horizontal Dimension (Vertical Dim - 1, Horizontal Dim - 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP),

    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 0)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 0), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim - 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM - 1), INVALID_PARAM),

    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 0)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim - 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM - 1), INVALID_PARAM),

    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 0)", 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 0), INVALID_PARAM),
    std::make_tuple("Accessing Valid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim - 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP),

    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim - 1, Horizontal Dim + 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),

    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 0)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 0), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 0)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim - 1, Horizontal Dim + 0)", 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 0), INVALID_PARAM),

    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim - 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM - 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim - 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM - 1), INVALID_PARAM),
    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim - 1, Horizontal Dim - 1)", 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP)

));


TEST(RBG565RGBWrite, WriteRGBToInvalidMatrix) 
{
    matrix* mat = nullptr;

    mat_fn_status status = write_rgb565_pixel_rgb(mat, 0xFF, 0xFF, 0xFF, 1, 1);

    ASSERT_EQ(status, NULL_MAT);
}


class WriteRgb565RGBPixelValueTestFixture : public testing::TestWithParam<std::tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, uint16_t>>  {
};

/**
 * @brief Parameterized method that will validate that the value
 * written at a specific (row,col) position equals the expected value.
 */
TEST_P(WriteRgb565RGBPixelValueTestFixture, ValidatePixelValue)
{
    std::string testCaseTitle;
    uint8_t red, green, blue;
    uint16_t row, col, true_color;
    std::tie(testCaseTitle, red, green, blue, row, col, true_color) = GetParam();

    std::cout << "Test Case: " << testCaseTitle << std::endl;
    std::cout << "\t\tParameters: \n";
    std::cout << "\t\tred: 0x" << std::hex << static_cast<uint16_t>(red) << std::endl;
    std::cout << "\t\tgreen: 0x" << std::hex << static_cast<uint16_t>(green) << std::endl;
    std::cout << "\t\tblue: 0x" << std::hex << static_cast<uint16_t>(blue) << std::endl;
    std::cout << "\t\trow: " << std::hex << row << std::endl;
    std::cout << "\t\tcol: " << std::to_string(col) << std::endl;
    std::cout << "\t\ttrue color: 0x" << std::hex << true_color << std::endl;

    matrix* mat = allocate_dummy_matrix();

    mat_fn_status status = write_rgb565_pixel_rgb(mat, red, green, blue, row, col);

    ASSERT_EQ(status, VALID_OP);

    uint32_t position = calculate_offset(mat, row, col);

    std::cout << "\tMatrix position pixel value: 0x" << std::hex << mat->mem[position] << std::endl;

    ASSERT_EQ(mat->mem[position], true_color);
}

INSTANTIATE_TEST_SUITE_P(WriteRGB565PixelValue, WriteRgb565RGBPixelValueTestFixture, testing::Values(
    std::make_tuple("Validate writing RGB value 0x00 0x00 0x00 equates to 0x0000", 0x00, 0x00, 0x00, 5, 5, 0x0000),
    std::make_tuple("Validate writing RGB value 0xFF 0xFF 0xFF equates to 0xFFFF", 0xFF, 0xFF, 0xFF, 5, 5, 0xFFFF),
    std::make_tuple("Validate writing RGB value 0xFF 0x00 0x00 equates to 0xF800 (Red occupies last 5 bits)", 0xFF, 0x00, 0x00, 5, 5, 0xF800),
    std::make_tuple("Validate writing RGB value 0x00 0xFF 0x00 equates to 0x07E0 (Green occupies middle 6 bits)", 0x00, 0xFF, 0x00, 5, 5, 0x07E0),
    std::make_tuple("Validate writing RGB value 0x00 0x00 0xFF equates to 0x001F (Blue occupes first 5 bits)", 0x00, 0x00, 0xFF, 5, 5, 0x001F),
    std::make_tuple("Validate writing RGB value 0xFF 0xFF 0x00 equates to 0x001F (Last 11 bits equal 1)", 0xFF, 0xFF, 0x00, 5, 5, 0xFFE0),
    std::make_tuple("Validate writing RGB value 0xFF 0x00 0xFF equates to 0x001F (First 5 and last 5 bits are equal to 1)", 0xFF, 0x00, 0xFF, 5, 5, 0xF81F),
    std::make_tuple("Validate writing RGB value 0x00 0xFF 0xFF equates to 0x001F (First 11 bits equal 1)", 0x00, 0xFF, 0xFF, 5, 5, 0x07FF)
));

class FillPixelValidateInputsTextFixture : public testing::TestWithParam<std::tuple<std::string,matrix*, uint8_t, uint8_t, uint8_t, mat_fn_status, mat_fn_status>> {
};

TEST_P(FillPixelValidateInputsTextFixture, ValidateFillPixelInputs) {
    std::string testCaseTitle;
    matrix* mat = nullptr;
    uint8_t pt_size, row, col;
    mat_fn_status expected_status, expected_deallocation_status;

    std::tie(testCaseTitle, mat, pt_size, row, col, expected_status, expected_deallocation_status) = GetParam();

    std::cout << "Test Case: " << testCaseTitle << std::endl;
    std::cout << "\t\tParameters: \n";
    std::cout << "\t\tpoint size: " << pt_size << std::endl;
    std::cout << "\t\trow: " << std::hex << row << std::endl;
    std::cout << "\t\tcol: " << std::to_string(col) << std::endl;
    std::cout << "\t\texpected status: " << expected_status << std::endl;
    std::cout << "\t\texpected deallocation status: " << expected_deallocation_status << std::endl;

    mat_fn_status stat = fill_pixel(mat, 0xFFFF, pt_size, row, col);

    ASSERT_EQ(stat, expected_status);

    stat = deallocate_matrix(mat);

    ASSERT_EQ(stat, expected_deallocation_status);
}

INSTANTIATE_TEST_SUITE_P(FillPixelInputValues, FillPixelValidateInputsTextFixture, testing::Values(
    std::make_tuple("Write to Null Matrix", nullptr, 1, 1, 1, NULL_MAT, NULL_MAT),

    std::make_tuple("Write to Invalid Row Dimension (VERTICAL_DIM + 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 1), 1, INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row Dimension (VERTICAL_DIM + 0)", allocate_dummy_matrix(), 1, (VERTICAL_DIM), 1, INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Valid Row Dimension (VERTICAL_DIM - 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), 1, VALID_OP, VALID_OP),

    std::make_tuple("Write to Invalid Column Dimension (HORIZONTAL_DIM + 1)", allocate_dummy_matrix(), 1, 1, (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Column Dimension (HORIZONTAL_DIM + 0)", allocate_dummy_matrix(), 1, 1, (HORIZONTAL_DIM), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Valid Column Dimension (HORIZONTAL_DIM - 1)", allocate_dummy_matrix(), 1, 1, (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 0)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM - 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 0)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM - 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 0)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM - 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM + 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM + 0)", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM - 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM + 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 0)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 0)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM + 0)", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM - 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM - 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM - 1)", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),

    std::make_tuple("Fill pixel in matrix with 0pt size", allocate_dummy_matrix(), 0, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Fill pixel in matrix with -1pt size (pt parameter is uint8_t. Be warned and turn on implicit conversions)", allocate_dummy_matrix(), -1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Fill pixel in matrix with 1pt size", allocate_dummy_matrix(), 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),
    std::make_tuple("Fill pixel in matrix with 100pt size (Shows that internal bounding logic functions)", allocate_dummy_matrix(), 100, 1, 1, VALID_OP, VALID_OP)
));

// Vertical line verification is a very interesting to test.
//  -> Likely we need to do bounds checking first.
//  -> Then we will need to do sample manual verification that
//      the data written out is what we expect it to be.    

//TEST(DrawVerticalLine, sample) 
//{
//    matrix* mat = allocate_dummy_matrix();
//
//    uint16_t color = 0xFFFF;
//    uint16_t pt_size = 1;
//    uint16_t col = 5;
//    uint16_t start_row = 1;
//    uint16_t end_row = 4;
//}

int main(int argc, char* argv[]) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}