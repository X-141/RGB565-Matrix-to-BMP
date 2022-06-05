#ifndef BITMAP_H
#define BITMAP_H

#include "matrix.h"

struct BMPFileHeader
{
    uint8_t file_type[2];
    uint8_t file_size[4];
    uint8_t reserved_1[2];
    uint8_t reserved_2[2];
    uint8_t offset_data[4];
};

struct BMPFileHeader *allocate_bmpfileheader();

void deallocate_bmpfileheader(struct BMPFileHeader *bmpFileHeaderPtr);

void set_bmpfileheader_filesize(const struct matrix *mat, struct BMPFileHeader *bmpFileHeaderPtr);

struct BMPInfoHeader
{
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

struct BMPInfoHeader *allocate_bmpinfoheader();

void deallocate_bmpinfoheader(struct BMPInfoHeader *bmpInfoHeaderPtr);

void set_bmpinfoheader_dimensions(const struct matrix *mat, struct BMPInfoHeader *bmpInfoHeaderPtr);

struct BMPColorHeader
{
    uint8_t red_mask[4];
    uint8_t green_mask[4];
    uint8_t blue_mask[4];
    uint8_t alpha_mask[4];

    uint8_t color_space_type[4];
    uint8_t unused[64];
};

struct BMPColorHeader *allocate_bmpcolorheader();

void deallocate_bmpcolorheader(struct BMPColorHeader *bmpColorHeaderPtr);

void write_rgb565_bmpfile(const char *filepath, struct matrix *mat);

#endif