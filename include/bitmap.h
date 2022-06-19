#ifndef BITMAP_H
#define BITMAP_H

#include "matrix.h"

/**
 * @brief General information for the image processor to help it understand how to 
 * begin reading our BMP file.
 */
struct BMPFileHeader {
  uint8_t file_type[2];
  uint8_t file_size[4];
  uint8_t reserved_1[2];
  uint8_t reserved_2[2];
  uint8_t offset_data[4];
};

/**
 * @brief Allocate a new BMP file header for BMP file generation. If 
 * allocation fails. NULL will be returned;
 * 
 * @return struct BMPFileHeader* 
 */
struct BMPFileHeader *allocate_bmpfileheader();

/**
 * @brief Deallocate existing BMP file header structure.
 * 
 * @param bmpFileHeaderPtr Pointer to an existing Bitmap File Header.
 */
void deallocate_bmpfileheader(struct BMPFileHeader *bmpFileHeaderPtr);

/**
 * @brief Sets the filesize field of the Bitmap Filesize header.
 * 
 * @param mat Pointer to existing Matrix structure
 * @param bmpFileHeaderPtr Pointer to existing File Header
 */
void set_bmpfileheader_filesize(const struct matrix *mat,
                                struct BMPFileHeader *bmpFileHeaderPtr);

/**
 * @brief Structure to represent the context of the image (what exactly are the
 * dimensions, size, how many bits per pixel, etc).
 */
struct BMPInfoHeader {
  uint8_t header_size[4];

  int8_t width[4];
  int8_t height[4];

  uint8_t planes[2];
  uint8_t bit_count[2];

  uint8_t compression[4];
  uint8_t size_image[4];

  uint8_t x_pixels_per_meter[4];
  uint8_t y_pixels_per_meter[4];

  uint8_t colors_used[4];
  uint8_t colors_important[4];
};

/**
 * @brief Allocate a new BMP info header for file generation.
 * 
 * Returns pointer to Bitmap Info header. If allocation fails, NULL will be returned.
 * 
 * @return struct BMPInfoHeader* 
 */
struct BMPInfoHeader *allocate_bmpinfoheader();

/**
 * @brief Deallocate existing info header stucture.
 * 
 * @param bmpInfoHeaderPtr Pointer to existing BMP info header.
 */
void deallocate_bmpinfoheader(struct BMPInfoHeader *bmpInfoHeaderPtr);

/**
 * @brief Set the fields in the info header to specify the dimensions of the matrix.
 * 
 * @param mat Pointer to existing matrix structure
 * @param bmpInfoHeaderPtr Pointer to existing info header
 */
void set_bmpinfoheader_dimensions(const struct matrix *mat,
                                  struct BMPInfoHeader *bmpInfoHeaderPtr);

/**
 * @brief Header stucture that informs the image processor how to read in the pixel data.
 */
struct BMPColorHeader {
  uint8_t red_mask[4];
  uint8_t green_mask[4];
  uint8_t blue_mask[4];
  uint8_t alpha_mask[4];

  uint8_t unused[68];
};

/**
 * @brief Allocate a new BMP color header for file generation.
 * 
 * Return pointer to Bitmap Color Header. If allocation fails, NULL will be returned.
 * 
 * @return struct BMPColorHeader* 
 */
struct BMPColorHeader *allocate_bmpcolorheader();

/**
 * @brief Deallocate bmp color header.
 * 
 * @param bmpColorHeaderPtr Pointer to an existing BMP color header
 */
void deallocate_bmpcolorheader(struct BMPColorHeader *bmpColorHeaderPtr);

/**
 * @brief Given a matrix containing arbitrary dimensions and data, write the data out 
 * to a to-be created BMP file.
 * 
 * @param filepath Destination file to write BMP data to.
 * @param mat Matrix used as source data to write out.
 * 
 * Returns 0 on success. Non-zero otherwize.
 * 
 * @return uint8_t 
 */
uint8_t write_rgb565_bmpfile(const char *filepath, struct matrix *mat);

#endif
