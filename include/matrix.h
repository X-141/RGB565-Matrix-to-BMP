#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

/// <summary>
/// Enumeration of possible function status messages.
/// </summary>
enum mat_fn_status { VALID_OP, NULL_MAT, NULL_MAT_MEMORY, INVALID_DIMENSION };

/// <summary>
/// Data structure for representing a traditional matrix structure
/// in similar libraries and package.
/// </summary>
struct matrix {
  /// <summary>
  /// Absolute size of the underlying memory pointed by *mem
  /// </summary>
  uint32_t size;

  /// <summary>
  /// Horizontal dimension of the matrix
  /// </summary>
  uint16_t horizontal;

  /// <summary>
  /// Vertical dimension of the matrix
  /// </summary>
  uint16_t vertical;

  /// <summary>
  /// Number of channels at a given x,y index.
  /// </summary>
  uint8_t channel;

  /// <summary>
  /// Pointer to the underlying memory representing the matrix.
  /// </summary>
  uint8_t *mem;
};

/// <summary>
/// Zero out matrix data with 0x00
/// </summary>
/// <param name="mat">Pointer to an existing matrix structure</param>
/// <returns>VALID_OP on success, not otherwise.</returns>
enum mat_fn_status zero_matrix(struct matrix *mat);

/// <summary>
/// Allocate a new matrix given a horizontal and vertical dimension.
/// </summary>
/// <param name="horizontal_dim">Indicate the horizontal dimension for
/// matrix</param> <param name="vertical_dim">Indicate the vertical dimension
/// for the matrix structure</param> <returns>Pointer to a newly allocated
/// matrix, NULL otherwise.</returns>
struct matrix *allocate_matrix(uint16_t horizontal_dim, uint16_t vertical_dim);

/// <summary>
/// Deallocate existing matrix structure
/// </summary>
/// <param name="mat">Pointer to a matrix struct</param>
/// <returns>Return VALID_OP on success, not otherwise.</return>
enum mat_fn_status deallocate_matrix(struct matrix *mat);

/// <summary>
/// Print out to console the entire matrix structure. Used for debugging.
/// </summary>
/// <param name="mat">Pointer to a matrix struct</param>
/// <returns>Return VALID_OP on success, not otherwise.</returns>
enum mat_fn_status print_matrix(struct matrix *mat);

/// <summary>
/// Given individually specified color values, write data at position column,
/// row
/// </summary>
/// <param name="red">Red color to write</param>
/// <param name="green">Green color to write</param>
/// <param name="blue">Blue color to write</param>
/// <param name="mat">Pointer to a matrix struct</param>
/// <param name="row">Row position to write color to</param>
/// <param name="column">Column position to write color to</param>
/// <returns>Return VALID_OP on success, not otherwise.</returns>
enum mat_fn_status write_rgb565_pixel_rgb(uint8_t red, uint8_t green,
                                          uint8_t blue, struct matrix *mat,
                                          uint16_t row, uint16_t column);

/// <summary>
/// Given a color code, write data at position column,row
/// </summary>
/// <param name="color">Color code to write at given position</param>
/// <param name="row">Row position to write color to</param>
/// <param name="mat">Pointer to a matrix struct</param>
/// <param name="column">Column position to write color to</param>
/// <returns>Return VALID_OP on success, not otherwise.</returns>
enum mat_fn_status write_rgb565_pixel_code(uint16_t color, struct matrix *mat,
                                           uint16_t row, uint16_t column);

#endif
