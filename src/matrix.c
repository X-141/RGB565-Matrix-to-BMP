#include <errno.h>
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

  uint8_t *mem = mat->mem;
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
  mat->channel = 3;

  mat->size = mat->horizontal * mat->vertical * mat->channel;
  mat->mem = (uint8_t *)malloc(sizeof(uint8_t) * (mat->size));

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
    mat->channel = -1;
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

  uint16_t x_row, y_column, x_offset, y_offset;
  uint8_t z_channel;
  printf("[\n");
  for (x_row = 0; x_row < mat->vertical; x_row++) {
    x_offset = x_row * mat->horizontal * mat->channel;
    printf("[");
    for (y_column = 0; y_column < mat->horizontal; y_column++) {
      y_offset = y_column * mat->channel;
      printf("[");
      for (z_channel = 0; z_channel < mat->channel; z_channel++) {
        printf("%3d", mat->mem[x_offset + y_offset + z_channel]);
      }
      printf("  ]");
    }
    printf("]\n");
  }
  printf("]\n");

  return VALID_OP;
}

static uint32_t calculate_offset(uint16_t row, uint16_t column,
                                 struct matrix *mat) {
  return (uint32_t)(row * mat->horizontal * mat->channel +
                    column * mat->channel);
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

  uint32_t offset = calculate_offset(row, column, mat);

  mat->mem[offset + 0] = red & RED_PIXEL_MASK;
  mat->mem[offset + 1] = green & GREEN_PIXEL_MASK;
  mat->mem[offset + 2] = blue & BLUE_PIXEL_MASK;

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

  uint32_t offset = calculate_offset(row, column, mat);

  mat->mem[offset + 0] = (color >> 11) & RED_PIXEL_MASK;  // RED
  mat->mem[offset + 1] = (color >> 5) & GREEN_PIXEL_MASK; // GREEN
  mat->mem[offset + 2] = (color & BLUE_PIXEL_MASK);       // BLUE

  return VALID_OP;
}
