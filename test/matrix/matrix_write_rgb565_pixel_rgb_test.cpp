//#include "gtest/gtest.h"
//#include "matrix.h"
//
//constexpr uint8_t HORIZONTAL_DIM = 10;
//constexpr uint8_t VERTICAL_DIM = 10;
//
//// Reference: https://www.sandordargo.com/blog/2019/04/24/parameterized-testing-with-gtest
//class WriteRGB565RGBDimensionTestFixture : public testing::TestWithParam<std::tuple<std::string, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, mat_fn_status>>  {
//};
//
///**
// * @brief Parameterized method that validates that write_rgb565_pixel_rbg()
// * will return the appropriate enum value depending on col, row input values.
// */
//TEST_P(WriteRGB565RGBDimensionTestFixture, ValidateDimensionRestriction) 
//{
//    std::string testCaseTitle;
//    uint16_t horizontal_dim, vertical_dim;
//    uint8_t red, green, blue;
//    uint16_t row, col;
//    mat_fn_status expected_status;
//    std::tie(testCaseTitle, horizontal_dim, vertical_dim, red, green, blue, row, col, expected_status) = GetParam();
//    //const auto [testCaseTitle, red, green, blue, row, col] = GetParam();
//
//    std::cout << "Test Case: " << testCaseTitle << std::endl;
//    std::cout << "\tParameters: \n";
//    std::cout << "\t\tred: 0x" << std::hex << static_cast<uint16_t>(red) << std::endl;
//    std::cout << "\t\tgreen: 0x" << std::hex << static_cast<uint16_t>(green) << std::endl;
//    std::cout << "\t\tblue: 0x" << std::hex << static_cast<uint16_t>(blue) << std::endl;
//    std::cout << "\t\trow: " << std::hex << row << std::endl;
//    std::cout << "\t\tcol: " << std::to_string(col) << std::endl;
//    std::cout << "\t\texpected stat: " << expected_status << "\n";
//
//    matrix* mat = allocate_matrix(horizontal_dim, vertical_dim);
//
//    ASSERT_NE(mat, nullptr);
//
//    mat_fn_status status = write_rgb565_pixel_rgb(mat, red, green, blue, row, col);
//
//    std::cout << "result stat: " << status << "\n";
//
//    ASSERT_EQ(status, expected_status);
//
//    status = deallocate_matrix(mat);
//
//    ASSERT_EQ(status, VALID_OP);
//}
//
///**
//* Parameterized test cases to validate various inputs permutations.
//*/
//INSTANTIATE_TEST_SUITE_P(WriteToInvalidDimensions, WriteRGB565RGBDimensionTestFixture, testing::Values(
//    std::make_tuple("Accessing Invalid Row Dimension (Vertical Dim + 1) ", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), 0, INVALID_PARAM),
//    std::make_tuple("Accessomg Invalid Row Dimension (Vertical Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM), 0x00, INVALID_PARAM),
//    std::make_tuple("Accessing Valid Row Dimension (Vertical Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), 0x00, VALID_OP),
//    std::make_tuple("Accessing Invalid Row Dimension (Negative Value)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, -1, 0x00, INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Column Dimension (Horizontal Dim + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, 0x00, (HORIZONTAL_DIM + 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Column Dimension (Horizontal Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, 0x00, (HORIZONTAL_DIM), INVALID_PARAM),
//    std::make_tuple("Accessing Valid Column Dimension (Horizontal Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, 0x00, (HORIZONTAL_DIM - 1), VALID_OP),
//    std::make_tuple("Accessing Invalid Column Dimension (Negative Value)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, 0x00, -1, INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM),
//    std::make_tuple("Accessing Valid Row and Horizontal Dimension (Vertical Dim - 1, Horizontal Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP),
//
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 0), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM - 1), INVALID_PARAM),
//
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM - 1), INVALID_PARAM),
//
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 0), INVALID_PARAM),
//    std::make_tuple("Accessing Valid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP),
//
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim - 1, Horizontal Dim + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 1), INVALID_PARAM),
//
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 0), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim - 1, Horizontal Dim + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 0), INVALID_PARAM),
//
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 1, Horizontal Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 1), (HORIZONTAL_DIM - 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim + 0, Horizontal Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM + 0), (HORIZONTAL_DIM - 1), INVALID_PARAM),
//    std::make_tuple("Accessing Invalid Row and Horizontal Dimension (Vertical Dim - 1, Horizontal Dim - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP)
//
//));
//
//class WriteRgb565RGBPixelValueTestFixture : public testing::TestWithParam<std::tuple<std::string, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, uint16_t>>  {
//};
//
///**
// * @brief Parameterized method that will validate that the value
// * written at a specific (row,col) position equals the expected value.
// */
//TEST_P(WriteRgb565RGBPixelValueTestFixture, ValidatePixelValue)
//{
//    std::string testCaseTitle;
//    uint16_t horizontal_dim, vertical_dim;
//    uint8_t red, green, blue;
//    uint16_t row, col, true_color;
//    std::tie(testCaseTitle, horizontal_dim, vertical_dim, red, green, blue, row, col, true_color) = GetParam();
//
//    std::cout << "Test Case: " << testCaseTitle << std::endl;
//    std::cout << "\t\tParameters: \n";
//    std::cout << "\t\tred: 0x" << std::hex << static_cast<uint16_t>(red) << std::endl;
//    std::cout << "\t\tgreen: 0x" << std::hex << static_cast<uint16_t>(green) << std::endl;
//    std::cout << "\t\tblue: 0x" << std::hex << static_cast<uint16_t>(blue) << std::endl;
//    std::cout << "\t\trow: " << std::hex << row << std::endl;
//    std::cout << "\t\tcol: " << std::to_string(col) << std::endl;
//    std::cout << "\t\ttrue color: 0x" << std::hex << true_color << std::endl;
//
//    matrix* mat = allocate_matrix(horizontal_dim, vertical_dim);
//
//    ASSERT_NE(mat, nullptr);
//
//    mat_fn_status status = write_rgb565_pixel_rgb(mat, red, green, blue, row, col);
//
//    ASSERT_EQ(status, VALID_OP);
//
//    uint32_t position = calculate_offset(mat, row, col);
//
//    std::cout << "\tMatrix position pixel value: 0x" << std::hex << mat->mem[position] << std::endl;
//
//    ASSERT_EQ(mat->mem[position], true_color);
//}
//
///**
//* Validate input RGB value and the resulting value written to the matrix.
//*/
//INSTANTIATE_TEST_SUITE_P(WriteRGB565PixelValue, WriteRgb565RGBPixelValueTestFixture, testing::Values(
//    std::make_tuple("Validate writing RGB value 0x00 0x00 0x00 equates to 0x0000", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0x00, 5, 5, 0x0000),
//    std::make_tuple("Validate writing RGB value 0xFF 0xFF 0xFF equates to 0xFFFF", HORIZONTAL_DIM, VERTICAL_DIM, 0xFF, 0xFF, 0xFF, 5, 5, 0xFFFF),
//    std::make_tuple("Validate writing RGB value 0xFF 0x00 0x00 equates to 0xF800 (Red occupies last 5 bits)", HORIZONTAL_DIM, VERTICAL_DIM, 0xFF, 0x00, 0x00, 5, 5, 0xF800),
//    std::make_tuple("Validate writing RGB value 0x00 0xFF 0x00 equates to 0x07E0 (Green occupies middle 6 bits)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0xFF, 0x00, 5, 5, 0x07E0),
//    std::make_tuple("Validate writing RGB value 0x00 0x00 0xFF equates to 0x001F (Blue occupes first 5 bits)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0x00, 0xFF, 5, 5, 0x001F),
//    std::make_tuple("Validate writing RGB value 0xFF 0xFF 0x00 equates to 0x001F (Last 11 bits equal 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0xFF, 0xFF, 0x00, 5, 5, 0xFFE0),
//    std::make_tuple("Validate writing RGB value 0xFF 0x00 0xFF equates to 0x001F (First 5 and last 5 bits are equal to 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0xFF, 0x00, 0xFF, 5, 5, 0xF81F),
//    std::make_tuple("Validate writing RGB value 0x00 0xFF 0xFF equates to 0x001F (First 11 bits equal 1)", HORIZONTAL_DIM, VERTICAL_DIM, 0x00, 0xFF, 0xFF, 5, 5, 0x07FF)
//));
