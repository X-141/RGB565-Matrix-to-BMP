#include "bitmap.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BMP_FILE_HEADER_SIZE (uint8_t)(14) // 14 bytes long
#define BMP_INFO_HEADER_SIZE (uint8_t)(40) // 40 bytes long
#define BMP_COLR_HEADER_SIZE (uint8_t)(84) // 84 bytes long

struct BMPFileHeader *allocate_bmpfileheader() {
  struct BMPFileHeader *ptr =
      (struct BMPFileHeader *)malloc(sizeof(struct BMPFileHeader));

  if (ptr == NULL) {
    printf("allocate_bmpfileheader: Failed to allocate BMPFileHeader.\n");
    return NULL;
  }

  uint16_t *file_type = (uint16_t *)ptr->file_type;
  *file_type = 0x4D42;

  uint32_t *file_size = (uint32_t *)ptr->file_size;
  *file_size = 0x00000000;

  uint16_t *reserved_1 = (uint16_t *)ptr->reserved_1;
  *reserved_1 = 0x0000;

  uint16_t *reserved_2 = (uint16_t *)ptr->reserved_2;
  *reserved_2 = 0x0000;

  uint32_t *offset_data = (uint32_t *)ptr->offset_data;
  *offset_data = 0x0000008A;

  return ptr;
}

void deallocate_bmpfileheader(struct BMPFileHeader *bmpFileHeaderPtr) {
  if (bmpFileHeaderPtr == NULL)
    return;
  free(bmpFileHeaderPtr);
}

void set_bmpfileheader_filesize(const struct matrix *mat,
                                struct BMPFileHeader *bmpFileHeaderPtr) {
  if (mat == NULL) {
    printf("set_bmpfilesize: mat passed in is NULL.\n");
    return;
  }

  if (bmpFileHeaderPtr == NULL) {
    printf("set_bmpfilesize: bmpFileHeader passed in is NULL.\n");
    return;
  }

  uint32_t *file_size = (uint32_t *)bmpFileHeaderPtr->file_size;
  *file_size = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE +
               BMP_COLR_HEADER_SIZE + (mat->horizontal * mat->vertical);
}

struct BMPInfoHeader *allocate_bmpinfoheader() {
  struct BMPInfoHeader *ptr =
      (struct BMPInfoHeader *)malloc(sizeof(struct BMPInfoHeader));

  if (ptr == NULL) {
    printf("allocate_bmpinfoheader: Failed to allocate BMPInfoHeader.\n");
    return NULL;
  }

  uint32_t *header_size = (uint32_t *)ptr->header_size;
  *header_size = 0x0000007C;

  int32_t *width = (int32_t *)ptr->width;
  *width = 0x00000000;

  int32_t *height = (int32_t *)ptr->height;
  *height = 0x00000000;

  uint16_t *planes = (uint16_t *)ptr->planes;
  *planes = 0x0001;

  uint16_t *bit_count = (uint16_t *)ptr->bit_count;
  *bit_count = 0x0010;

  uint32_t *compression = (uint32_t *)ptr->compression;
  *compression = 0x00000003;

  uint32_t *size_image = (uint32_t *)ptr->size_image;
  *size_image = 0x00000000;

  uint32_t *x_pixels_per_meter = (uint32_t *)ptr->x_pixels_per_meter;
  *x_pixels_per_meter = 0x00000000;

  uint32_t *y_pixels_per_meter = (uint32_t *)ptr->y_pixels_per_meter;
  *y_pixels_per_meter = 0x00000000;

  uint32_t *color_used = (uint32_t *)ptr->colors_used;
  *color_used = 0x00000000;

  uint32_t *colors_important = (uint32_t *)ptr->colors_important;
  *colors_important = 0x00000000;

  return ptr;
}

void deallocate_bmpinfoheader(struct BMPInfoHeader *bmpInfoHeaderPtr) {
  if (bmpInfoHeaderPtr == NULL)
    return;
  free(bmpInfoHeaderPtr);
}

void set_bmpinfoheader_dimensions(const struct matrix *mat,
                                  struct BMPInfoHeader *bmpInfoHeaderPtr) {
  if (mat == NULL) {
    printf("set_bmp_width_height: mat passed in is NULL.\n");
    return;
  }

  if (bmpInfoHeaderPtr == NULL) {
    printf("set_bmp_width_height: bmpInfoHeaderPtr passed in is NULL.\n");
    return;
  }

  int32_t *width = (int32_t *)bmpInfoHeaderPtr->width;
  *width = mat->horizontal;

  int32_t *height = (int32_t *)bmpInfoHeaderPtr->height;
  *height = mat->vertical;

  uint32_t *image_size = (uint32_t *)bmpInfoHeaderPtr->size_image;
  *image_size = mat->horizontal * mat->vertical;
}

struct BMPColorHeader *allocate_bmpcolorheader() {
  struct BMPColorHeader *ptr =
      (struct BMPColorHeader *)malloc(sizeof(struct BMPColorHeader));

  if (ptr == NULL) {
    printf("Unable to allocate BMPColorHeader.\n");
    return NULL;
  }

  uint32_t *red_mask = (uint32_t *)ptr->red_mask;
  *red_mask = 0x0000f800; // Written to file as 00F8 0000

  uint32_t *green_mask = (uint32_t *)ptr->green_mask;
  *green_mask = 0x000007E0; // Written to file as E007 0000

  uint32_t *blue_mask = (uint32_t *)ptr->blue_mask;
  *blue_mask = 0x0000001F; // Written to file as 1F00 0000

  uint32_t *alpha_mask = (uint32_t *)ptr->alpha_mask;
  *alpha_mask = 0x00000000;

  for (uint8_t index = 0; index < 68; index++) {
    ptr->unused[index] = 0x00;
  }

  return ptr;
}

void deallocate_bmpcolorheader(struct BMPColorHeader *bmpColorHeaderPtr) {
  if (bmpColorHeaderPtr == NULL)
    return;
  free(bmpColorHeaderPtr);
}

uint8_t write_rgb565_bmpfile(const char *filepath, struct matrix *mat) {
  if (mat == NULL) {
    printf("Unable to write BMP file, passed in mat parameter is NULL.\n");
    return 1;
  }

  uint8_t ret = 0;
  struct BMPFileHeader *header_ptr = allocate_bmpfileheader();
  struct BMPInfoHeader *info_ptr = allocate_bmpinfoheader();
  struct BMPColorHeader *color_ptr = allocate_bmpcolorheader();

  if (header_ptr == NULL) {
    printf("Unable to allocate BMPFileHeader.\n");
    ret = 1;
    goto cleanup;
  }

  if (info_ptr == NULL) {
    printf("Unable to allocate BMPInfoHeader.\n");
    ret = 2;
    goto cleanup;
  }

  if (color_ptr == NULL) {
    printf("Unable to allocate BMPColorHeader.\n");
    ret = 3;
    goto cleanup;
  }

  set_bmpfileheader_filesize(mat, header_ptr);
  set_bmpinfoheader_dimensions(mat, info_ptr);
  FILE *fileptr = NULL;
  errno_t err = fopen_s(&fileptr, filepath, "wb");
  if (err != 0) {
    printf("Unable to open %s for binary writing.\n", filepath);
    ret = 4;
    goto cleanup;
  }

  fwrite(header_ptr, sizeof(struct BMPFileHeader), 1, fileptr);
  fwrite(info_ptr, sizeof(struct BMPInfoHeader), 1, fileptr);
  fwrite(color_ptr, sizeof(struct BMPColorHeader), 1, fileptr);

  uint16_t padding = 0x0000;
  bool toggle_padding = ((mat->horizontal % 2) == 0) ? false : true;
  for (int32_t row = (mat->vertical - 1); row >= 0; row--) {
    for (int32_t col = 0; col < mat->horizontal; col++) {
      // uint32_t offset = calculate_offset(row, col, mat);
      // printf("offset: %d.\n", offset);
      fwrite((mat->mem + calculate_offset(row, col, mat)), sizeof(uint16_t), 1,
             fileptr);
    }
    if (toggle_padding)
      fwrite(&padding, sizeof(uint16_t), 1, fileptr);
  }

  fclose(fileptr);

cleanup:
  if (color_ptr)
    deallocate_bmpcolorheader(color_ptr);
  if (info_ptr)
    deallocate_bmpinfoheader(info_ptr);
  if (header_ptr)
    deallocate_bmpfileheader(header_ptr);

  return ret;
}
