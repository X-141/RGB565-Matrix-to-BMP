#include "gtest/gtest.h"
#include "matrix.h"

/**
* Having issues paramaterizing these sorts of test cases.
* The issue is that I would like to make the expected matrix value 
* visible the developer. However, attempts have lead to typing issues
* 
* In the future these unit tests can be improved with parameterized testing.
*/

constexpr uint8_t EVEN_HORIZONTAL_DIM = 10;
constexpr uint8_t EVEN_VERTICAL_DIM = 10;

constexpr uint8_t ODD_HORIZONTAL_DIM = 9;
constexpr uint8_t ODD_VERTICAL_DIM = 9;

void performMatrixValidation(matrix* resultingMatrix, uint16_t* validationMatrix, uint16_t vertical_dim, uint16_t horizontal_dim) {
    uint16_t x_row, y_col, offset;
    for (x_row = 0; x_row < vertical_dim; ++x_row) {
        offset = x_row * horizontal_dim;
        for (y_col = 0; y_col < horizontal_dim; ++y_col) {
            //std::cout << "x_row: " << x_row << " " << "y_col: " << y_col << std::endl;
            //std::cout << "\t" << validationMatrix[x_row][y_col] << std::endl;
            //std::cout << "\t" << resultingMatrix->mem[offset + y_col] << std::endl;
            ASSERT_EQ(validationMatrix[offset + y_col], resultingMatrix->mem[offset + y_col]);
        }
    }
}

void performVerticalLineDraw(std::string& testCaseTitle, uint16_t* validMat, uint16_t horizontalDim, uint16_t verticalDim,
    uint16_t color, uint16_t ptSize, uint16_t col, uint16_t startRow, uint16_t endRow, mat_fn_status expectedStatus) {
    std::cout << "Test Case: " << testCaseTitle << std::endl;
    std::cout << "\t\tParameters: \n";
    std::cout << "\t\tcolor: " << color << std::endl;
    std::cout << "\t\tptSize: " << ptSize << std::endl;
    std::cout << "\t\tcol: " << col << std::endl;
    std::cout << "\t\tstartRow: " << startRow << std::endl;
    std::cout << "\t\tendRow: " << endRow << std::endl;

    matrix* mat = allocate_matrix(horizontalDim, verticalDim);
    ASSERT_NE(mat, nullptr);

    mat_fn_status status = draw_vertical_line(mat, color, ptSize, col, startRow, endRow);
    ASSERT_EQ(status, expectedStatus);

    performMatrixValidation(mat, validMat, verticalDim, horizontalDim);

    status = deallocate_matrix(mat);
    ASSERT_EQ(status, VALID_OP);
}

TEST(DrawVerticalLineValidationEvenEven, SampleDrawVerticalLine)
{
    std::string testCaseTitle = "Sample Vertical Line Draw Test";

    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t col = 6;
    uint16_t start_row = 1;
    uint16_t end_row = 4;
    mat_fn_status expected_status = VALID_OP;
    
    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, ValidateStartAndEndValues)
{
    std::string testCaseTitle = "Sample Vertical Line Draw Test";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t col = 6;
    uint16_t start_row = 1;
    uint16_t end_row = 1;
    mat_fn_status expected_status = VALID_OP;

    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, EndRowIsLessThanStartRow)
{
    std::string testCaseTitle = "End Row Is Less Than Starting Row";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t col = 6;
    uint16_t start_row = 4;
    uint16_t end_row = 1;
    mat_fn_status expected_status = INVALID_PARAM;

    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, InvalidPtSize)
{
    std::string testCaseTitle = "Invalid Pt Size";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 0;
    uint16_t col = 6;
    uint16_t start_row = 1;
    uint16_t end_row = 4;
    mat_fn_status expected_status = INVALID_PARAM;

    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, ValidateColValuesAboveLimit)
{
    std::string testCaseTitle = "Validate Col Value Above limit";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 1;
    uint16_t end_row = 4;

    uint16_t col = EVEN_HORIZONTAL_DIM;
    mat_fn_status expected_status = INVALID_PARAM;
    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, ValidateColValuesOnLimit)
{
    std::string testCaseTitle = "Validate Col Value On limit";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 1;
    uint16_t end_row = 4;

    uint16_t col = EVEN_HORIZONTAL_DIM - 1;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, ValidateColValuesOneBelowLimit)
{
    std::string testCaseTitle = "Validate Col Value One Below Limit";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 1;
    uint16_t end_row = 4;

    uint16_t col = EVEN_HORIZONTAL_DIM - 2;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, ValidateColLimitWithCompleteVerticalDraw)
{
    std::string testCaseTitle = "Validate Col Limit with Complete Vertical Draw";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 0;
    uint16_t end_row = EVEN_VERTICAL_DIM-1;

    uint16_t col = EVEN_HORIZONTAL_DIM - 1;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, ValidateMinColLimitWithCompleteVerticalDraw)
{
    std::string testCaseTitle = "Validate Min Col Limit with Complete Vertical Draw";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 0;
    uint16_t end_row = EVEN_VERTICAL_DIM-1;

    uint16_t col = 0;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, ValidateColValueFlooredDiv2FullVerticalDraw)
{
    std::string testCaseTitle = "Validate Col Value Div2 minus 1 Vertical Draw";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 0;
    uint16_t end_row = EVEN_VERTICAL_DIM-1;

    uint16_t col = (EVEN_HORIZONTAL_DIM/2)-1;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenEven, ValidateColValueCeilDiv2FullVerticalDraw)
{
    std::string testCaseTitle = "Validate Col Value Div2 Full Vertical Draw";
    uint16_t validMat[EVEN_VERTICAL_DIM * EVEN_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 0;
    uint16_t end_row = EVEN_VERTICAL_DIM - 1;

    uint16_t col = EVEN_HORIZONTAL_DIM / 2;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, EVEN_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, SampleDrawVerticalLine)
{
    std::string testCaseTitle = "Sample Vertical Line Draw Test";

    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0xFFFF, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t col = 5;
    uint16_t start_row = 1;
    uint16_t end_row = 4;
    mat_fn_status expected_status = VALID_OP;

    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, ValidateStartAndEndValues)
{
    std::string testCaseTitle = "Sample Vertical Line Draw Test";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t col = 4;
    uint16_t start_row = 1;
    uint16_t end_row = 1;
    mat_fn_status expected_status = VALID_OP;

    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, EndRowIsLessThanStartRow)
{
    std::string testCaseTitle = "End Row Is Less Than Starting Row";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t col = 6;
    uint16_t start_row = 4;
    uint16_t end_row = 1;
    mat_fn_status expected_status = INVALID_PARAM;

    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, InvalidPtSize)
{
    std::string testCaseTitle = "Invalid Pt Size";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 0;
    uint16_t col = 6;
    uint16_t start_row = 1;
    uint16_t end_row = 4;
    mat_fn_status expected_status = INVALID_PARAM;

    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, ValidateColValuesAboveLimit)
{
    std::string testCaseTitle = "Validate Col Value Above limit";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 1;
    uint16_t end_row = 4;

    uint16_t col = ODD_HORIZONTAL_DIM;
    mat_fn_status expected_status = INVALID_PARAM;
    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, ValidateColValuesOnLimit)
{
    std::string testCaseTitle = "Validate Col Value On limit";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 1;
    uint16_t end_row = 4;

    uint16_t col = ODD_HORIZONTAL_DIM - 1;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, ValidateColValuesOneBelowLimit)
{
    std::string testCaseTitle = "Validate Col Value One Below Limit";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0,
        0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0,
        0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0,
        0, 0, 0, 0, 0, 0, 0, 0xFFFF, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 1;
    uint16_t end_row = 4;

    uint16_t col = ODD_HORIZONTAL_DIM - 2;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, ValidateColLimitWithCompleteVerticalDraw)
{
    std::string testCaseTitle = "Validate Col Limit with Complete Vertical Draw";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 0;
    uint16_t end_row = EVEN_VERTICAL_DIM - 1;

    uint16_t col = ODD_HORIZONTAL_DIM - 1;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, ValidateMinColLimitWithCompleteVerticalDraw)
{
    std::string testCaseTitle = "Validate Min Col Limit with Complete Vertical Draw";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 0;
    uint16_t end_row = EVEN_VERTICAL_DIM - 1;

    uint16_t col = 0;
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}

TEST(DrawVerticalLineValidationEvenOdd, ValidateColValueFlooredDiv2FullVerticalDraw)
{
    std::string testCaseTitle = "Validate Col Value Div2 floored Vertical Draw";
    uint16_t validMat[EVEN_VERTICAL_DIM * ODD_HORIZONTAL_DIM] = {
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFFFF, 0, 0, 0, 0,
    };
    uint16_t color = 0xFFFF;
    uint16_t pt_size = 1;
    uint16_t start_row = 0;
    uint16_t end_row = EVEN_VERTICAL_DIM - 1;

    uint16_t col = floor(ODD_HORIZONTAL_DIM / 2);
    mat_fn_status expected_status = VALID_OP;
    performVerticalLineDraw(testCaseTitle, validMat, ODD_HORIZONTAL_DIM, EVEN_VERTICAL_DIM, color, pt_size, col, start_row, end_row, expected_status);
}
