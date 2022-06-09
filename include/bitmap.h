#ifndef BITMAP_H
#define BITMAP_H

#include "matrix.h"

/// <summary>
/// General information for the image processor to help it understand how to
/// begin reading our BMP file
/// </summary>
struct BMPFileHeader {
  uint8_t file_type[2];
  uint8_t file_size[4];
  uint8_t reserved_1[2];
  uint8_t reserved_2[2];
  uint8_t offset_data[4];
};

/// <summary>
/// Allocate a new BMP file header for BMP file generation
/// </summary>
/// <returns>A pointer to a newly created BMP file header. NULL
/// otherwise</returns>
struct BMPFileHeader *allocate_bmpfileheader();

/// <summary>
/// Deallocate existing BMP file header structure.
/// </summary>
/// <param name="bmpFileHeaderPtr"></param>
void deallocate_bmpfileheader(struct BMPFileHeader *bmpFileHeaderPtr);

/// <summary>
/// Set the filesize field in the File header structure.
/// </summary>
/// <param name="mat">Pointer to existing Matrix structure</param>
/// <param name="bmpFileHeaderPtr">Pointer to existing File Header</param>
void set_bmpfileheader_filesize(const struct matrix *mat,
                                struct BMPFileHeader *bmpFileHeaderPtr);

/// <summary>
/// Structure to represent the context of the image (what exactly are the
/// dimensions, size, how many bits per pixel, etc).
/// </summary>
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

/// <summary>
/// Allocate a new BMP info header for file generation.
/// </summary>
/// <returns>Pointer to newly allocated BMP info header. NULL
/// otherwise.</returns>
struct BMPInfoHeader *allocate_bmpinfoheader();

/// <summary>
/// Deallocate existing info header stucture
/// </summary>
/// <param name="bmpInfoHeaderPtr">Pointer to existing BMP info header.</param>
void deallocate_bmpinfoheader(struct BMPInfoHeader *bmpInfoHeaderPtr);

/// <summary>
/// Set the fields in the info header to specify the dimensions of the matrix.
/// </summary>
/// <param name="mat">Pointer to existing matrix structure</param>
/// <param name="bmpInfoHeaderPtr">Pointer to existing info header</param>
void set_bmpinfoheader_dimensions(const struct matrix *mat,
                                  struct BMPInfoHeader *bmpInfoHeaderPtr);

/// <summary>
/// Header stucture that informs the image processor how to read in the pixel
/// data.
/// </summary>
struct BMPColorHeader {
  uint8_t red_mask[4];
  uint8_t green_mask[4];
  uint8_t blue_mask[4];
  uint8_t alpha_mask[4];

  uint8_t unused[68];
};

/// <summary>
/// Allocate a new BMP color header for file generation
/// </summary>
/// <returns>Returns pointer to newly allocated BMPColorHeader on success. NULL
/// otherwise.</returns
struct BMPColorHeader *allocate_bmpcolorheader();

/// <summary>
/// Deallocate bmp color header
/// </summary>
/// <param name="bmpColorHeaderPtr">Pointer to an existing BMP color header
/// struct</param>
void deallocate_bmpcolorheader(struct BMPColorHeader *bmpColorHeaderPtr);

/// <summary>
/// Given a matrix containing arbitrary dimensions and data, write the data out
/// to a to-be created BMP file.
/// </summary>
/// <param name="filepath">Destination file to write BMP data to.</param>
/// <param name="mat">Matrix used as source data to write out.</param>
/// <returns>Status code of function execution. Non-zero on failure.</returns>
uint8_t write_rgb565_bmpfile(const char *filepath, struct matrix *mat);

#endif
