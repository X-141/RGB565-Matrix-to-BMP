#include "gtest/gtest.h"
#include "matrix.h"

/**
 * @brief Validate that if passed a zero-zero dimension sized
 * matrix, that no matrix will be allocated.
 */
TEST(MatrixSetupSuite, ValidateZeroZeroMatrix)
{
    matrix* mat = allocate_matrix(0, 0);

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

    matrix* mat = allocate_matrix(horizontal_dim, vertical_dim);

    for (uint32_t index = 0; index < (horizontal_dim * vertical_dim); ++index) {
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

    matrix* mat = allocate_matrix(horizontal_dim, vertical_dim);

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
    matrix* mat = allocate_matrix(1, 1);

    ASSERT_NE(mat, nullptr);

    mat_fn_status status = deallocate_matrix(mat);

    ASSERT_EQ(status, VALID_OP);
}

