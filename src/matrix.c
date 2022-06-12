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

enum mat_fn_status zero_matrix(struct matrix *mat) {
  if (!mat) {
    printf("zero_matrix: data_ptr is NULL.\n");
    return NULL_MAT;
  }

  if (!(mat->mem)) {
    printf("zero_matrix: data_ptr underlying data is NULL.\n");
    return NULL_MAT_MEMORY;
  }

  uint16_t *mem = mat->mem;
  for (uint32_t index = 0; index < mat->size; index++) {
    mem[index] = 0;
  }

  return VALID_OP;
}

struct matrix *allocate_matrix(uint16_t horizontal_dim, uint16_t vertical_dim) {
  struct matrix *mat = (struct matrix *)malloc(sizeof(struct matrix));
  if (!mat) {
    printf("allocate_matrix: failed to allocate matrix_info struct.\n");
    return NULL;
  }

  mat->horizontal = horizontal_dim;
  mat->vertical = vertical_dim;

  mat->size = mat->horizontal * mat->vertical;
  mat->mem = (uint16_t *)malloc(sizeof(uint16_t) * (mat->size));

  if (mat->mem == NULL) {
    printf("Unable to allocate underlying memory space for matrix.\n");
    free(mat);
    return NULL;
  }

  zero_matrix(mat);

  return mat;
}

enum mat_fn_status deallocate_matrix(struct matrix *mat) {

  if (mat != NULL && mat->mem) {
    free(mat->mem);
    mat->horizontal = -1;
    mat->vertical = -1;
    mat->size = -1;

    free(mat);
    return VALID_OP;
  }
  return NULL_MAT;
}

enum mat_fn_status print_matrix(struct matrix *mat) {
  if (mat == NULL) {
    printf("print_matrix: mat passed is NULL.\n");
    return NULL_MAT;
  }

  uint16_t x_row, y_column, offset;
  printf("[\n");
  for (x_row = 0; x_row < mat->vertical; x_row++) {
    offset = x_row * mat->horizontal;
    printf("[");
    for (y_column = 0; y_column < mat->horizontal; y_column++) {
      printf("[ %6d ]", mat->mem[offset + y_column]);
    }
    printf("]\n");
  }
  printf("]\n");

  return VALID_OP;
}

uint32_t calculate_offset(uint16_t row, uint16_t column, struct matrix *mat) {
  return (uint32_t)(row * mat->horizontal + column);
}

enum mat_fn_status write_rgb565_pixel_rgb(uint8_t red, uint8_t green,
                                          uint8_t blue, struct matrix *mat,
                                          uint16_t row, uint16_t column) {
  if (mat == NULL) {
    printf("write_rgb565_pixel: mat passed is NULL.\n");
    return NULL_MAT;
  }

  if (row < 0 || row >= mat->vertical) {
    printf("write_rgb565_pixel: row parameters is invalid.\n");
    return INVALID_DIMENSION;
  }

  if (column < 0 || column >= mat->horizontal) {
    printf("write_rgb565_pixel: column parameters is invalid.\n");
    return INVALID_DIMENSION;
  }

  uint16_t *ptr = mat->mem + calculate_offset(row, column, mat);

  *ptr = 0x0000;
  *ptr |= (red & RED_PIXEL_MASK) << 11;
  *ptr |= (green & GREEN_PIXEL_MASK) << 5;
  *ptr |= (blue & BLUE_PIXEL_MASK);

  return VALID_OP;
}

enum mat_fn_status write_rgb565_pixel_code(uint16_t color, struct matrix *mat,
                                           uint16_t row, uint16_t column) {
  if (mat == NULL) {
    printf("write_rgb565_pixel_code: mat passed is NULL.\n");
    return NULL_MAT;
  }

  if (row < 0 || row >= mat->vertical) {
    printf("write_rgb565_pixel: row parameters is invalid.\n");
    return INVALID_DIMENSION;
  }

  if (column < 0 || column >= mat->horizontal) {
    printf("write_rgb565_pixel: column parameters is invalid.\n");
    return INVALID_DIMENSION;
  }

  mat->mem[calculate_offset(row, column, mat)] = color;

  return VALID_OP;
}

bool static validate_horizontal_dimension(uint16_t horizontal_dim,
                                          uint16_t start_x, uint16_t end_x) {
  if (start_x >= horizontal_dim || start_x < 0) {
    printf("validate_horizontal_dimension: start_x dimension is invalid");
    return false;
  }

  if (end_x >= horizontal_dim || end_x < 0) {
    printf("validate_horizontal_dimension: end_x dimension is invalid");
    return false;
  }

  return true;
}

bool static validate_vertical_dimension(uint16_t vertical_dim, uint16_t start_y,
                                        uint16_t end_y) {
  if (start_y >= vertical_dim || start_y < 0) {
    printf("validate_vertical_dimension: start_y dimension is invalid");
    return false;
  }

  if (start_y >= vertical_dim || start_y < 0) {
    printf("validate_vertical_dimension: end_y dimension is invalid");
    return false;
  }

  return true;
}

bool static validate_points_fall_in_bounds(uint16_t horizontal_dim,
                                           uint16_t vertical_dim,
                                           uint16_t start_x, uint16_t start_y,
                                           uint16_t end_x, uint16_t end_y) {

  if (validate_horizontal_dimension(horizontal_dim, start_x, end_x)) {
    printf("validate_points_fall_in_bounds: horizontal dimensions found to be "
           "invalid.\n");
    return false;
  }

  if (validate_vertical_dimension(vertical_dim, start_y, end_y)) {
    printf("validate_points_fall_in_bounds: vertical dimensions found to be "
           "invalid.\n");
    return false;
  }

  return true;
}

uint8_t static fill_pixel(uint16_t color, uint16_t pt_size, struct matrix *mat,
                          uint16_t row, uint16_t column) {

  if (pt_size == 0) {
    printf("Invalid pixel size. returning.\n");
    return 1;
  } else if (pt_size == 1) {
    uint32_t offset = calculate_offset(row, column, mat);
    printf("Writing 0xFFFF to (%d, %d).\n", column, row);
    printf("%ul calculate_offset(row, column, mat)offset.\n", offset);
    mat->mem[offset] = color;
    return 0;
  }

  uint16_t position_offset = pt_size - 1;

  int32_t start_position_row = row - position_offset;
  int32_t start_position_column = column - position_offset;

  int32_t end_position_row = row + position_offset;
  int32_t end_position_column = column + position_offset;
  if (start_position_row < 0) {
    start_position_row = 0;
  }

  if (start_position_column < 0) {
    start_position_column = 0;
  }

  if (end_position_row >= mat->vertical) {
    end_position_row = mat->vertical - 1;
  }

  if (end_position_column >= mat->horizontal) {
    end_position_column = mat->horizontal - 1;
  }

  printf("Starting (%d, %d) to Ending (%d, %d).\n", start_position_column,
         start_position_row, end_position_column, end_position_row);

  for (uint16_t row = start_position_row; row <= end_position_row; row++) {
    for (uint16_t col = start_position_column; col <= end_position_column;
         col++) {
      uint32_t offset = calculate_offset(row, col, mat);
      printf("Writing 0xFFFF to (%d, %d).\n", col, row);
      printf("%ul offset.\n", offset);
      mat->mem[offset] = color;
    }
  }

  return 0;
}

void draw_vertical_line(uint16_t color, uint16_t pt_size, struct matrix *mat,
                        uint16_t col_position, uint16_t start_row,
                        uint16_t end_row) {
  if (mat == NULL) {
    printf("draw_vertical_line: mat passed is NULL.\n");
    return;
  }

  if (start_row == end_row) {
    fill_pixel(color, pt_size, mat, start_row, col_position);
    return;
  }

  if (start_row > end_row) {
    printf("draw_vertical_line: start_row is less than end_row.\n");
    return;
  }

  bool valid_dims =
      validate_vertical_dimension(mat->vertical, start_row, end_row);
  if (col_position < 0 || col_position >= mat->horizontal || !valid_dims) {
    printf("draw_vertical_line: Invalid dimensions detected.\n");
    return;
  }

  for (uint16_t row = start_row; row < end_row; row++) {
    fill_pixel(color, pt_size, mat, row, col_position);
  }
}

void draw_horizontal_line(uint16_t color, uint16_t pt_size, struct matrix *mat,
                          uint16_t row, uint16_t start_col, uint16_t end_col) {
  if (mat == NULL) {
    printf("draw_horizontal_line: mat passed is NULL.\n");
    return;
  }

  if (start_col == end_col) {
    fill_pixel(color, pt_size, mat, row, start_col);
    return;
  }

  if (start_col > end_col) {
    printf("draw_horizontal_line: Starting column is greater than ending "
           "column. returning.\n");
    return;
  }

  if (row < 0 || row >= mat->vertical) {
    printf("draw_horizontal_line: row dimension is invalid.\n");
    return;
  }

  bool valid_dims =
      validate_horizontal_dimension(mat->horizontal, start_col, end_col);

  if (!valid_dims) {
    printf(
        "draw_perfect_horizontal_line: Invalid dimension found, returning.\n");
    return;
  }

  for (uint16_t x = start_col; x <= end_col; x++) {
    fill_pixel(color, pt_size, mat, row, x);
  }
}

void draw_rectangle(uint16_t color, uint16_t pt_size, struct matrix *mat,
                    uint16_t start_x, uint16_t start_y, uint16_t end_x,
                    uint16_t end_y) {

  if (mat == NULL) {
    printf("draw_rectangle: mat passed is NULL.\n");
    return;
  }

  // Check if coordinates are within bounds.
  uint8_t valid_dims = validate_points_fall_in_bounds(
      mat->horizontal, mat->vertical, start_x, start_y, end_x, end_y);

  draw_horizontal_line(color, pt_size, mat, start_y, start_x, end_x);
  draw_horizontal_line(color, pt_size, mat, end_y, start_x, end_x);

  draw_vertical_line(color, pt_size, mat, start_x, start_y, end_y);
  draw_vertical_line(color, pt_size, mat, end_x, start_y, end_y);

  if (valid_dims) {
    printf("draw_rectangle: Invalid dimension found, returning.\n");
    return;
  }
}
