#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration of possible function status messages.
 */
typedef enum mat_fn_status
{
  VALID_OP,
  NULL_MAT,
  INVALID_PARAM,
  FAILED_MAT_ALLOCATION,
  FAILED_BINARY_FILE_READ,
  FAILED_DRAW_OP
} mat_fn_status;

/**
 * @brief Data structure for representing a traditional matrix structure
 * in similar libraries and package.
 *
 */
typedef struct matrix
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
} matrix;

/**
 * @brief Zero out matrix data with 0x00.
 *
 * VALID_OP on success, not otherwise.
 *
 * @param mat Pointer to an existing matrix structure
 * @return enum mat_fn_status
 */
mat_fn_status zero_matrix(matrix *mat);

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
mat_fn_status deallocate_matrix(matrix *mat);

/**
 * @brief Print out to console the entire matrix structure. Used for debugging.
 *
 * Return VALID_OP on success, not otherwise.
 *
 * @param mat Pointer to a matrix struct.
 * @return enum mat_fn_status
 */
mat_fn_status print_matrix(matrix *mat);

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
uint32_t calculate_offset(matrix *mat, uint16_t row, uint16_t column);

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
mat_fn_status write_rgb565_pixel_rgb(matrix *mat, uint8_t red,
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
mat_fn_status write_rgb565_pixel_code(matrix *mat, uint16_t color,
                                      uint16_t row, uint16_t column);

/**
 * @brief At a given (row, column) position, fill pixels in and around
 * the point according to the pt_size value indicated.
 * 
 * The way the pixel is filled is in a rectangular fashion. So if we
 * have a given position "pos_x, pos_x", the bound for the rectangular fill is:
 * (pos_x - (pt -1)), (pos_y - (pt - 1)) to (pos_x + (pt - 1)), (pos_y + (pt - 1))
 * 
 * @param mat Pointer to matrix structure.
 * @param color Color of the pixel
 * @param pt_size Size of the pixel drawn
 * @param row Position x
 * @param column Position y
 * @return uint8_t 
 */
mat_fn_status fill_pixel(matrix *mat, uint16_t color, uint16_t pt_size,
                          uint16_t row, uint16_t column);

/**
 * @brief Given a x position (column), draw a straight line from start_y to end_y.
 *
 * @param mat Pointer to matrix structure.
 * @param color Color of the line.
 * @param pt_size Size of the line.
 * @param col_position Column position to draw line.
 * @param start_row Starting row position.
 * @param end_row Ending row position.
 */
mat_fn_status draw_vertical_line(matrix *mat, uint16_t color, uint16_t pt_size,
                                 uint16_t col_position, uint16_t start_row,
                                 uint16_t end_row);

/**
 * @brief Given a y position (row), draw a straight line from start_x to end_x.
 *
 * @param mat Pointer to matrix structure.
 * @param color Color of the line.
 * @param pt_size Size of the line.
 * @param y_position Row position to draw line.
 * @param start_x Starting column position.
 * @param end_x Ending column position.
 */
mat_fn_status draw_horizontal_line(matrix *mat, uint16_t color, uint16_t pt_size,
                                   uint16_t y_position, uint16_t start_x,
                                   uint16_t end_x);

/**
 * @brief Draw rectangle starting from one corner (start_x, start_y) to opposite corner (end_x, end_y)
 *
 * @param mat Pointer to matrix structure.
 * @param color Color of the rectangle.
 * @param pt_size Size of the lines.
 * @param start_x X position of initial corner.
 * @param start_y Y position of initial corner.
 * @param end_x X position of opposite corner.
 * @param end_y Y position of opposite corner.
 */
mat_fn_status draw_rectangle(matrix *mat, uint16_t color, uint16_t pt_size,
                             uint16_t start_x, uint16_t start_y, uint16_t end_x,
                             uint16_t end_y);

/**
 * @brief Given a filepath, read in the binary data and store it into the dimensions of a pre-allocated matrix structure.
 *
 * Returns boolean to indicate success.
 *
 * @param mat Pointer to matrix structure. Ideally should be intialized to contain only zero's
 * @param filepath Filepath to an existing file containing raw data.
 * @return bool
 */
mat_fn_status read_binary_file(matrix *mat, const char *filepath);

#ifdef __cplusplus
}
#endif

#endif