#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enumeration of possible function status messages.
 */
enum mat_fn_status
{
  VALID_OP,
  NULL_MAT,
  NULL_MAT_MEMORY,
  INVALID_DIMENSION
};

/**
 * @brief Data structure for representing a traditional matrix structure
 * in similar libraries and package.
 *
 */
struct matrix
{

  /**
   * @brief Absolute size of the underlying memory pointed by *mem
   */
  uint32_t size;

  /**
   * @brief Horizontal dimension of the matrix.
   */
  uint16_t horizontal;

  /**
   * @brief Vertical dimension of the matrix.
   */
  uint16_t vertical;

  /**
   * @brief Pointer to the underlying memory representing the matrix.
   */
  uint16_t *mem;
};

/**
 * @brief Zero out matrix data with 0x00.
 *
 * VALID_OP on success, not otherwise.
 *
 * @param mat Pointer to an existing matrix structure
 * @return enum mat_fn_status
 */
enum mat_fn_status zero_matrix(struct matrix *mat);

/**
 * @brief Allocate a new matrix given a horizontal and vertical dimension.
 *
 * Pointer to a newly allocated matrix, NULL otherwise.
 *
 * @param horizontal_dim Indicate the horizontal dimension for matrix
 * @param vertical_dim Indicate the vertical dimension for the matrix structure
 * @return struct matrix*
 */
struct matrix *allocate_matrix(uint16_t horizontal_dim, uint16_t vertical_dim);

/**
 * @brief Deallocate existing matrix structure.
 *
 * Return VALID_OP on success, not otherwise.
 *
 * @param mat Pointer to a matrix struct.
 * @return enum mat_fn_status
 */
enum mat_fn_status deallocate_matrix(struct matrix *mat);

/**
 * @brief Print out to console the entire matrix structure. Used for debugging.
 *
 * Return VALID_OP on success, not otherwise.
 *
 * @param mat Pointer to a matrix struct.
 * @return enum mat_fn_status
 */
enum mat_fn_status print_matrix(struct matrix *mat);

/**
 * @brief Given a matrix and position (row, column), calculate the position in the underlying
 * matrix memory to retrieve the correct pixel.
 *
 * Returns calculated index position.
 *
 * @param mat existing pointer to a matrix structure.
 * @param row Row position in the matrix.
 * @param column Column position in the matrix.
 * @return uint32_t
 */
uint32_t calculate_offset(struct matrix *mat, uint16_t row, uint16_t column);

/**
 * @brief Given individually specified color values, write data at position (column, row).
 *
 * Return VALID_OP on success, not otherwise.
 *
 * @param mat Pointer to a matrix struct.
 * @param red Red color to write.
 * @param green Green color to write.
 * @param blue Blue color to write.
 * @param row Row position to write color to.
 * @param column Column position to write color to.
 * @return enum mat_fn_status
 */
enum mat_fn_status write_rgb565_pixel_rgb(struct matrix *mat, uint8_t red, 
                                          uint8_t green, uint8_t blue,
                                          uint16_t row, uint16_t column);

/**
 * @brief Given a color code, write data at position (column, row).
 *
 * Return VALID_OP on success, not otherwise.
 *
 * @param mat Pointer to a matrix struct.
 * @param color Color code to write at given position.
 * @param row Row position to write color to.
 * @param column Column position to write color to.
 * @return enum mat_fn_status
 */
enum mat_fn_status write_rgb565_pixel_code(struct matrix *mat, uint16_t color,
                                           uint16_t row, uint16_t column);

/**
 * @brief Given a x position (column), draw a straight line from start_y to end_y.
 * @param mat Pointer to matrix structure.
 * @param color Color of the line.
 * @param pt_size Size of the line.
 * @param col_position Column position to draw line.
 * @param start_row Starting row position.
 * @param end_row Ending row position.
 */
void draw_vertical_line(struct matrix *mat, uint16_t color, uint16_t pt_size,
                        uint16_t col_position, uint16_t start_row,
                        uint16_t end_row);

/**
 * @brief Given a y position (row), draw a straight line from start_x to end_x.
 *
 * @param color Color of the line.
 * @param pt_size Size of the line.
 * @param mat Pointer to matrix structure.
 * @param y_position Row position to draw line.
 * @param start_x Starting column position.
 * @param end_x Ending column position.
 */
void draw_horizontal_line(struct matrix *mat, uint16_t color, uint16_t pt_size, 
                          uint16_t y_position, uint16_t start_x,
                          uint16_t end_x);

/**
 * @brief Draw rectangle starting from one corner (start_x, start_y) to opposite corner (end_x, end_y)
 *
 * @param color Color of the rectangle.
 * @param pt_size Size of the lines.
 * @param mat Pointer to matrix structure.
 * @param start_x X position of initial corner.
 * @param start_y Y position of initial corner.
 * @param end_x X position of opposite corner.
 * @param end_y Y position of opposite corner.
 */
void draw_rectangle(struct matrix *mat, uint16_t color, uint16_t pt_size, 
                    uint16_t start_x, uint16_t start_y, uint16_t end_x,
                    uint16_t end_y);

/**
 * @brief Given a filepath, read in the binary data and store it into the dimensions of a pre-allocated matrix structure.
 *
 * Returns boolean to indicate success.
 *
 * @param filepath Filepath to an existing file containing raw data.
 * @param mat Pointer to matrix structure. Ideally should be intialized to contain only zero's
 * @return bool
 */
bool read_binary_file(struct matrix *mat, const char *filepath);

#endif
