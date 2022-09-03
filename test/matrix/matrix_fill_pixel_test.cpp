#include "gtest/gtest.h"
#include "matrix.h"

constexpr uint8_t HORIZONTAL_DIM = 10;
constexpr uint8_t VERTICAL_DIM = 10;

TEST(FillPixelValidation, NullInputMat) {
    mat_fn_status stat = fill_pixel(nullptr, 0xFFFF, 1, 1, 1);
    ASSERT_EQ(stat, INVALID_PARAM);
}

class FillPixelValidateInputsTextFixture : public testing::TestWithParam<std::tuple<std::string, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t, mat_fn_status, mat_fn_status>> {
};

TEST_P(FillPixelValidateInputsTextFixture, ValidateFillPixelInputs) {
    std::string testCaseTitle;
    uint16_t horizontal_dim, vertical_dim;
    uint8_t pt_size, row, col;
    mat_fn_status expected_status, expected_deallocation_status;

    std::tie(testCaseTitle, horizontal_dim, vertical_dim, pt_size, row, col, expected_status, expected_deallocation_status) = GetParam();

    std::cout << "Test Case: " << testCaseTitle << std::endl;
    std::cout << "\t\tParameters: \n";
    std::cout << "\t\tpoint size: " << pt_size << std::endl;
    std::cout << "\t\trow: " << std::hex << row << std::endl;
    std::cout << "\t\tcol: " << std::to_string(col) << std::endl;
    std::cout << "\t\texpected status: " << expected_status << std::endl;
    std::cout << "\t\texpected deallocation status: " << expected_deallocation_status << std::endl;

    matrix* mat = allocate_matrix(horizontal_dim, vertical_dim);

    ASSERT_NE(mat, nullptr);

    mat_fn_status stat = fill_pixel(mat, 0xFFFF, pt_size, row, col);

    ASSERT_EQ(stat, expected_status);

    stat = deallocate_matrix(mat);

    ASSERT_EQ(stat, expected_deallocation_status);
}

INSTANTIATE_TEST_SUITE_P(FillPixelInputValues, FillPixelValidateInputsTextFixture, testing::Values(
    std::make_tuple("Write to Invalid Row Dimension (VERTICAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 1), 1, INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row Dimension (VERTICAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM), 1, INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Valid Row Dimension (VERTICAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), 1, VALID_OP, VALID_OP),

    std::make_tuple("Write to Invalid Column Dimension (HORIZONTAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, 1, (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Column Dimension (HORIZONTAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, 1, (HORIZONTAL_DIM), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Valid Column Dimension (HORIZONTAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, 1, (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM + 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 1), INVALID_PARAM, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM + 0)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM + 0), INVALID_PARAM, VALID_OP),

    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 1, HORIZONTAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 1), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM + 0, HORIZONTAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM + 0), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Write to Invalid Row and Column Dimension (VERTICAL_DIM - 1, HORIZONTAL_DIM - 1)", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),

    std::make_tuple("Fill pixel in matrix with 0pt size", HORIZONTAL_DIM, VERTICAL_DIM, 0, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Fill pixel in matrix with -1pt size (pt parameter is uint8_t. Be warned and turn on implicit conversions)", HORIZONTAL_DIM, VERTICAL_DIM, -1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), INVALID_PARAM, VALID_OP),
    std::make_tuple("Fill pixel in matrix with 1pt size", HORIZONTAL_DIM, VERTICAL_DIM, 1, (VERTICAL_DIM - 1), (HORIZONTAL_DIM - 1), VALID_OP, VALID_OP),
    std::make_tuple("Fill pixel in matrix with 100pt size (Shows that internal bounding logic functions)", HORIZONTAL_DIM, VERTICAL_DIM, 100, 1, 1, VALID_OP, VALID_OP)
));
