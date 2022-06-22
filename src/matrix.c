#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "stdio.h"

#define RED_PIXEL_MASK (uint8_t)(0x1F)
#define GREEN_PIXEL_MASK (uint8_t)(0x3F)
#define BLUE_PIXEL_MASK (uint8_t)(0x1F)

#ifdef __cplusplus
extern "C" {
#endif

mat_fn_status zero_matrix(matrix *mat)
{
  if (!mat)
  {
    printf("zero_matrix: data_ptr is NULL.\n");
    return INVALID_PARAM;
  }

  if (!(mat->mem))
  {
    printf("zero_matrix: data_ptr underlying data is NULL.\n");
    return INVALID_PARAM;
  }

  uint16_t *mem = mat->mem;
  for (uint32_t index = 0; index < mat->size; index++)
  {
    mem[index] = 0;
  }

  return VALID_OP;
}

struct matrix *allocate_matrix(uint16_t horizontal_dim, uint16_t vertical_dim)
{
  struct matrix *mat = (struct matrix *)malloc(sizeof(struct matrix));
  if (!mat)
  {
    printf("allocate_matrix: failed to allocate matrix_info struct.\n");
    return NULL;
  }

  mat->horizontal = horizontal_dim;
  mat->vertical = vertical_dim;

  mat->size = mat->horizontal * mat->vertical;
  mat->mem = (uint16_t *)malloc(sizeof(uint16_t) * (mat->size));

  if (mat->mem == NULL)
  {
    printf("Unable to allocate underlying memory space for matrix.\n");
    free(mat);
    return NULL;
  }

  zero_matrix(mat);

  return mat;
}

mat_fn_status deallocate_matrix(matrix *mat)
{
  if (mat != NULL && mat->mem)
  {
    free(mat->mem);
    mat->horizontal = -1;
    mat->vertical = -1;
    mat->size = -1;

    free(mat);
    return VALID_OP;
  }
  return INVALID_PARAM;
}

mat_fn_status print_matrix(matrix *mat)
{
  if (mat == NULL)
  {
    printf("print_matrix: mat passed is NULL.\n");
    return INVALID_PARAM;
  }

  uint16_t x_row, y_column, offset;
  printf("[\n");
  for (x_row = 0; x_row < mat->vertical; x_row++)
  {
    offset = x_row * mat->horizontal;
    printf("[");
    for (y_column = 0; y_column < mat->horizontal; y_column++)
    {
      printf("[ %6d ]", mat->mem[offset + y_column]);
    }
    printf("]\n");
  }
  printf("]\n");

  return VALID_OP;
}

uint32_t calculate_offset(matrix *mat, uint16_t row, uint16_t column)
{
  return (uint32_t)(row * mat->horizontal + column);
}

mat_fn_status write_rgb565_pixel_rgb(matrix *mat, uint8_t red, uint8_t green, uint8_t blue,
                                     uint16_t row, uint16_t column)
{
  if (mat == NULL)
  {
    printf("write_rgb565_pixel: mat passed is NULL.\n");
    return INVALID_PARAM;
  }

  if (row < 0 || row >= mat->vertical)
  {
    printf("write_rgb565_pixel: row parameters is invalid.\n");
    return INVALID_PARAM;
  }

  if (column < 0 || column >= mat->horizontal)
  {
    printf("write_rgb565_pixel: column parameters is invalid.\n");
    return INVALID_PARAM;
  }

  uint16_t *ptr = mat->mem + calculate_offset(mat, row, column);

  *ptr = 0x0000;
  *ptr |= (red & RED_PIXEL_MASK) << 11;
  *ptr |= (green & GREEN_PIXEL_MASK) << 5;
  *ptr |= (blue & BLUE_PIXEL_MASK);

  return VALID_OP;
}

mat_fn_status write_rgb565_pixel_code(matrix *mat, uint16_t color,
                                      uint16_t row, uint16_t column)
{
  if (mat == NULL)
  {
    printf("write_rgb565_pixel_code: mat passed is NULL.\n");
    return NULL_MAT;
  }

  if (row < 0 || row >= mat->vertical)
  {
    printf("write_rgb565_pixel: row parameters is invalid.\n");
    return INVALID_PARAM;
  }

  if (column < 0 || column >= mat->horizontal)
  {
    printf("write_rgb565_pixel: column parameters is invalid.\n");
    return INVALID_PARAM;
  }

  mat->mem[calculate_offset(mat, row, column)] = color;

  return VALID_OP;
}

bool static validate_horizontal_dimension(uint16_t horizontal_dim,
                                          uint16_t start_x, uint16_t end_x)
{
  if (start_x >= horizontal_dim || start_x < 0)
  {
    printf("validate_horizontal_dimension: start_x dimension is invalid");
    return false;
  }

  if (end_x >= horizontal_dim || end_x < 0)
  {
    printf("validate_horizontal_dimension: end_x dimension is invalid");
    return false;
  }

  return true;
}

bool static validate_vertical_dimension(uint16_t vertical_dim, uint16_t start_y,
                                        uint16_t end_y)
{
  if (start_y >= vertical_dim || start_y < 0)
  {
    printf("validate_vertical_dimension: start_y dimension is invalid");
    return false;
  }

  if (start_y >= vertical_dim || start_y < 0)
  {
    printf("validate_vertical_dimension: end_y dimension is invalid");
    return false;
  }

  return true;
}

bool static validate_points_fall_in_bounds(uint16_t horizontal_dim,
                                           uint16_t vertical_dim,
                                           uint16_t start_x, uint16_t start_y,
                                           uint16_t end_x, uint16_t end_y)
{

  if (!validate_horizontal_dimension(horizontal_dim, start_x, end_x))
  {
    printf("validate_points_fall_in_bounds: horizontal dimensions found to be "
           "invalid.\n");
    return false;
  }

  if (!validate_vertical_dimension(vertical_dim, start_y, end_y))
  {
    printf("validate_points_fall_in_bounds: vertical dimensions found to be "
           "invalid.\n");
    return false;
  }

  return true;
}

uint8_t static fill_pixel(matrix *mat, uint16_t color, uint16_t pt_size,
                          uint16_t row, uint16_t column)
{

  if (pt_size == 0)
  {
    printf("Invalid pixel size. returning.\n");
    return 1;
  }
  else if (pt_size == 1)
  {
    uint32_t offset = calculate_offset(mat, row, column);
    // printf("Writing 0xFFFF to (%d, %d).\n", column, row);
    // printf("%ul calculate_offset(row, column, mat)offset.\n", offset);
    mat->mem[offset] = color;
    return 0;
  }

  uint16_t position_offset = pt_size - 1;

  int32_t start_position_row = row - position_offset;
  int32_t start_position_column = column - position_offset;

  int32_t end_position_row = row + position_offset;
  int32_t end_position_column = column + position_offset;
  if (start_position_row < 0)
  {
    start_position_row = 0;
  }

  if (start_position_column < 0)
  {
    start_position_column = 0;
  }

  if (end_position_row >= mat->vertical)
  {
    end_position_row = mat->vertical - 1;
  }

  if (end_position_column >= mat->horizontal)
  {
    end_position_column = mat->horizontal - 1;
  }

  // printf("Starting (%d, %d) to Ending (%d, %d).\n", start_position_column,
  //       start_position_row, end_position_column, end_position_row);

  for (uint16_t row = start_position_row; row <= end_position_row; row++)
  {
    for (uint16_t col = start_position_column; col <= end_position_column;
         col++)
    {
      uint32_t offset = calculate_offset(mat, row, col);
      // printf("Writing 0xFFFF to (%d, %d).\n", col, row);
      // printf("%ul offset.\n", offset);
      mat->mem[offset] = color;
    }
  }

  return 0;
}

mat_fn_status draw_vertical_line(matrix *mat, uint16_t color, uint16_t pt_size,
                                 uint16_t col_position, uint16_t start_row,
                                 uint16_t end_row)
{
  if (mat == NULL)
  {
    printf("draw_vertical_line: mat passed is NULL.\n");
    return INVALID_PARAM;
  }

  if (start_row == end_row)
  {
    fill_pixel(mat, color, pt_size, start_row, col_position);
    return INVALID_PARAM;
  }

  if (start_row > end_row)
  {
    printf("draw_vertical_line: start_row is less than end_row.\n");
    return INVALID_PARAM;
  }

  bool valid_dims =
      validate_vertical_dimension(mat->vertical, start_row, end_row);
  if (col_position < 0 || col_position >= mat->horizontal || !valid_dims)
  {
    printf("draw_vertical_line: Invalid dimensions detected.\n");
    return INVALID_PARAM;
  }

  for (uint16_t row = start_row; row < end_row; row++)
  {
    fill_pixel(mat, color, pt_size, row, col_position);
  }

  return VALID_OP;
}

mat_fn_status draw_horizontal_line(matrix *mat, uint16_t color, uint16_t pt_size,
                                   uint16_t row, uint16_t start_col, uint16_t end_col)
{
  if (mat == NULL)
  {
    printf("draw_horizontal_line: mat passed is NULL.\n");
    return INVALID_PARAM;
  }

  if (start_col == end_col)
  {
    fill_pixel(mat, color, pt_size, row, start_col);
    return INVALID_PARAM;
  }

  if (start_col > end_col)
  {
    printf("draw_horizontal_line: Starting column is greater than ending "
           "column. returning.\n");
    return INVALID_PARAM;
  }

  if (row < 0 || row >= mat->vertical)
  {
    printf("draw_horizontal_line: row dimension is invalid.\n");
    return INVALID_PARAM;
  }

  bool valid_dims =
      validate_horizontal_dimension(mat->horizontal, start_col, end_col);

  if (!valid_dims)
  {
    printf(
        "draw_perfect_horizontal_line: Invalid dimension found, returning.\n");
    return INVALID_PARAM;
  }

  for (uint16_t x = start_col; x <= end_col; x++)
  {
    fill_pixel(mat, color, pt_size, row, x);
  }

  return VALID_OP;
}

mat_fn_status draw_rectangle(matrix *mat, uint16_t color, uint16_t pt_size,
                             uint16_t start_x, uint16_t start_y, uint16_t end_x,
                             uint16_t end_y)
{

  if (mat == NULL)
  {
    printf("draw_rectangle: mat passed is NULL.\n");
    return INVALID_PARAM;
  }

  // Check if coordinates are within bounds.
  bool valid_dims = validate_points_fall_in_bounds(
      mat->horizontal, mat->vertical, start_x, start_y, end_x, end_y);

  if (!valid_dims)
  {
    printf("draw_rectangle: Invalid dimension found, returning.\n");
    return INVALID_PARAM;
  }

  if(draw_horizontal_line(mat, color, pt_size, start_y, start_x, end_x) != VALID_OP) {
    printf("draw_rectangle: failed to draw top horizontal line\n");
    return FAILED_DRAW_OP;
  }

  if(draw_horizontal_line(mat, color, pt_size, end_y, start_x, end_x) != VALID_OP) {
    printf("draw_rectangle: failed to draw bottom horizontal line\n");
    return FAILED_DRAW_OP;
  }

  if(draw_vertical_line(mat, color, pt_size, start_x, start_y, end_y) != VALID_OP) {
    printf("draw_rectangle: failed to draw left vertical line\n");
    return FAILED_DRAW_OP;
  }

  if(draw_vertical_line(mat, color, pt_size, end_x, start_y, end_y) != VALID_OP) {
    printf("draw_rectangle: failed to draw right vertical line\n");
    return FAILED_DRAW_OP;
  }

  return VALID_OP;
}

mat_fn_status read_binary_file(matrix *mat, const char *filepath)
{

  if (mat == NULL)
  {
    printf("read_binary_file: mat structure pointer is NULL.\n");
    return INVALID_PARAM;
  }

  if (filepath == NULL)
  {
    printf("read_binary_file: filepath indicated is NULL.\n");
    return INVALID_PARAM;
  }

  FILE *file_ptr = NULL;
  file_ptr = fopen(filepath, "rb");
  if (file_ptr == NULL)
  {
    printf("read_binary_file: unable to open binary file for reading.\n");
    return FAILED_BINARY_FILE_READ;
  }

  size_t num_read = fread(mat->mem, sizeof(uint16_t), mat->size, file_ptr);

  mat_fn_status status = VALID_OP;

  if (!num_read)
  {
    printf("read_binary_file: fread returned zero.\n");
    status = FAILED_BINARY_FILE_READ;
  }

  fclose(file_ptr);

  return status;
}

#ifdef __cplusplus
}
#endif