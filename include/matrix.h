#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#define ERROR (int8_t)(-1)

#define UNSAFE_CALC_OFFSET(ROW, COL, MAT) (ROW * MAT->vertical * MAT->channel + COL * MAT->channel)

/**
 * @brief Data structure that encapsulates the matrix
 * struct def'n with information about how it's accessed.
 *
 * i.e. what are its dimensions and how are values stored
 * in the matrix.
 */
struct matrix
{
    uint32_t size;
    uint16_t horizontal;
    uint16_t vertical;
    uint8_t channel;
    uint8_t *mem;
};

/**
 * @brief Zero out underlying matrix data with 0.
 *
 * @param data_ptr Pointer to struct matrix_info.
 * @return Zero on success. Non-zero on error.
 */
int8_t zero_matrix(struct matrix *mat);

struct matrix *allocate_matrix(uint16_t horizontal_dim, uint16_t vertical_dim);

/**
 * @brief Deallocate data_ptr.
 *
 * @param data_ptr Pointer to a struct matrix_info that will be deallocated. Note, if parameter is
 * already NULL or the underlying memory is null, nothing will be performed.
 */
void deallocate_matrix(struct matrix *mat);

uint8_t print_matrix(struct matrix *mat);

uint32_t calculate_offset(uint16_t row, uint16_t column, struct matrix* mat);

void write_rgb565_pixel_rgb(uint8_t red, uint8_t green, uint8_t blue,
                        struct matrix *mat, uint16_t row, uint16_t column);

void write_rgb565_pixel_code(uint16_t color, struct matrix* mat, uint16_t row, uint16_t column);

#endif