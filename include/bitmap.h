#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <byteswap.h>

#include "matrix.h"

#define BMP_FILE_HEADER_SIZE (uint8_t)(14) // 14 bytes long
#define BMP_INFO_HEADER_SIZE (uint8_t)(40) // 40 bytes long
#define BMP_COLR_HEADER_SIZE (uint8_t)(84) // 84 bytes long

struct BMPFileHeader
{
    uint8_t file_type[2];
    uint8_t file_size[4];
    uint8_t reserved_1[2];
    uint8_t reserved_2[2];
    uint8_t offset_data[4];
};

struct BMPFileHeader *allocate_bmpfileheader()
{
    struct BMPFileHeader *ptr = (struct BMPFileHeader *)malloc(sizeof(struct BMPFileHeader));

    if (ptr == NULL)
    {
        printf("allocate_bmpfileheader: Failed to allocate BMPFileHeader.\n");
        return NULL;
    }

    uint16_t *file_type = (uint16_t *)ptr->file_type;
    *file_type = 0x4D42;

    uint32_t *file_size = (uint32_t *)ptr->file_size;
    // *file_size = 0x0000008E;
    *file_size = 0x00000000;

    uint16_t *reserved_1 = (uint16_t *)ptr->reserved_1;
    *reserved_1 = 0x0000;

    uint16_t *reserved_2 = (uint16_t *)ptr->reserved_2;
    *reserved_2 = 0x0000;

    uint32_t *offset_data = (uint32_t *)ptr->offset_data;
    *offset_data = 0x0000008A;

    return ptr;
}

void deallocate_bmpfileheader(struct BMPFileHeader *bmpFileHeaderPtr)
{
    if (bmpFileHeaderPtr == NULL)
        return;
    free(bmpFileHeaderPtr);
}

void set_bmpfileheader_filesize(const struct matrix *mat, struct BMPFileHeader *bmpFileHeaderPtr)
{
    if (mat == NULL)
    {
        printf("set_bmpfilesize: mat passed in is NULL.\n");
        return;
    }

    if (bmpFileHeaderPtr == NULL)
    {
        printf("set_bmpfilesize: bmpFileHeader passed in is NULL.\n");
        return;
    }

    uint32_t *file_size = (uint32_t *)bmpFileHeaderPtr->file_size;
    *file_size = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE + BMP_COLR_HEADER_SIZE + (mat->horizontal * mat->vertical * 4);
}

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

struct BMPInfoHeader *allocate_bmpinfoheader()
{
    struct BMPInfoHeader *ptr = (struct BMPInfoHeader *)malloc(sizeof(struct BMPInfoHeader));

    if (ptr == NULL)
    {
        printf("allocate_bmpinfoheader: Failed to allocate BMPInfoHeader.\n");
        return NULL;
    }

    uint32_t *header_size = (uint32_t *)ptr->header_size;
    *header_size = 0x0000007C;

    int32_t *width = (int32_t *)ptr->width;
    // *width = 0x00000001;
    *width = 0x00000000;

    int32_t *height = (int32_t *)ptr->height;
    // *height = 0x00000001;
    *height = 0x00000000;

    uint16_t *planes = (uint16_t *)ptr->planes;
    *planes = 0x0001;

    uint16_t *bit_count = (uint16_t *)ptr->bit_count;
    *bit_count = 0x0010;

    uint32_t *compression = (uint32_t *)ptr->compression;
    *compression = 0x00000000;

    uint32_t *size_image = (uint32_t *)ptr->size_image;
    *size_image = 0x00000004;

    uint32_t *x_pixels_per_meter = (uint32_t *)ptr->x_pixels_per_meter;
    *x_pixels_per_meter = 0x00002E23;

    uint32_t *y_pixels_per_meter = (uint32_t *)ptr->y_pixels_per_meter;
    *y_pixels_per_meter = 0x00002E23;

    uint32_t *color_used = (uint32_t *)ptr->colors_used;
    *color_used = 0x00000000;

    uint32_t *colors_important = (uint32_t *)ptr->colors_important;
    *colors_important - 0x00000000;

    return ptr;
}

void deallocate_bmpinfoheader(struct BMPInfoHeader *bmpInfoHeaderPtr)
{
    if (bmpInfoHeaderPtr == NULL)
        return;
    free(bmpInfoHeaderPtr);
}

void set_bmpinfoheader_dimensions(const struct matrix *mat, struct BMPInfoHeader *bmpInfoHeaderPtr)
{
    if (mat == NULL)
    {
        printf("set_bmp_width_height: mat passed in is NULL.\n");
        return;
    }

    if (bmpInfoHeaderPtr == NULL)
    {
        printf("set_bmp_width_height: bmpInfoHeaderPtr passed in is NULL.\n");
        return;
    }

    int32_t *width = (int32_t *)bmpInfoHeaderPtr->width;
    *width = mat->horizontal;

    int32_t *height = (int32_t *)bmpInfoHeaderPtr->height;
    *height = mat->vertical;
}

struct BMPColorHeader
{
    uint8_t red_mask[4];
    uint8_t green_mask[4];
    uint8_t blue_mask[4];
    uint8_t alpha_mask[4];

    uint8_t color_space_type[4];
    uint8_t unused[64];
};

struct BMPColorHeader *allocate_bmpcolorheader()
{
    struct BMPColorHeader *ptr = (struct BMPColorHeader *)malloc(sizeof(struct BMPColorHeader));

    uint32_t *red_mask = (uint32_t *)ptr->red_mask;
    *red_mask = 0x0000F800;

    uint32_t *green_mask = (uint32_t *)ptr->green_mask;
    *green_mask = 0x000007E0;

    uint32_t *blue_mask = (uint32_t *)ptr->blue_mask;
    *blue_mask = 0x0000001F;

    uint32_t *alpha_mask = (uint32_t *)ptr->alpha_mask;
    *alpha_mask = 0x00000000;

    uint32_t *color_space_type = (uint32_t *)ptr->color_space_type;
    *color_space_type = 0x73524742;

    for (uint8_t index = 0; index < 64; index++)
    {
        ptr->unused[index] = 0x00;
    }

    return ptr;
}

void deallocate_bmpcolorheader(struct BMPColorHeader *bmpColorHeaderPtr)
{
    if (bmpColorHeaderPtr == NULL)
        return;
    free(bmpColorHeaderPtr);
}

void write_rgb565_bmpfile(const char *filepath, struct matrix *mat)
{
    struct BMPFileHeader *header_ptr = allocate_bmpfileheader();
    struct BMPInfoHeader *info_ptr = allocate_bmpinfoheader();
    struct BMPColorHeader *color_ptr = allocate_bmpcolorheader();

    // TODO: This causes memory leaks
    if (header_ptr == NULL)
    {
        printf("Unable to allocate BMPFileHeader.\n");
        goto cleanup_file_header;
    }

    if (info_ptr == NULL)
    {
        printf("Unable to allocate BMPInfoHeader.\n");
        goto cleanup_info_header;
    }

    if (color_ptr == NULL)
    {
        printf("Unable to allocate BMPColorHeader.\n");
        goto cleanup_everything;
    }

    set_bmpfileheader_filesize(mat, header_ptr);
    set_bmpinfoheader_dimensions(mat, info_ptr);

    FILE *fileptr = fopen(filepath, "wb");
    if (fileptr == NULL)
    {
        printf("Unable to open %s for binary writing.\n", filepath);
        goto cleanup_everything;
    }

    fwrite(header_ptr, sizeof(struct BMPFileHeader), 1, fileptr);
    fwrite(info_ptr, sizeof(struct BMPInfoHeader), 1, fileptr);
    fwrite(color_ptr, sizeof(struct BMPColorHeader), 1, fileptr);

    uint16_t working_data = 0x0000;
    uint16_t green_data = 0x0000;
    uint16_t red_data = 0x0000;
    uint16_t blue_data = 0x0000;
    uint16_t red_color = 0x0000;
    uint16_t green_color = 0x0000;
    uint16_t blue_color = 0x0000;
    uint16_t padding = 0x0000;

    uint32_t index = 0;
    uint32_t row_raw_length = 0;
    int toggle_padding = (ceil((16.0 * mat->horizontal) / 32.0) * 4) - (mat->horizontal * 2);
    for (int32_t row = (mat->vertical - 1); row >= 0; row--)
    {
        index = UNSAFE_CALC_OFFSET(row, 0, mat);
        row_raw_length = (row + 1) * mat->horizontal * mat->channel;
        while (index < row_raw_length)
        {
            working_data = 0x0000;

            red_color = mat->mem[index] & 0x001F;
            red_color = bswap_16(red_color);
            red_data = 0x0000;
            red_data |= (red_color << 3);
            red_data &= 0xF800;

            // Likely a better way to write this
            green_color = mat->mem[index + 1] & 0x003F;
            green_color = bswap_16(green_color);
            green_data = 0x0000;
            green_data |= (green_color << 2);
            green_data &= 0xE000;
            green_data |= (green_color >> 8);
            green_data &= 0xE007;
            green_data = bswap_16(green_data);

            blue_color = mat->mem[index + 2] & 0x001F;
            blue_color = bswap_16(blue_color);
            blue_data = 0x0000;
            blue_data |= (mat->mem[index + 2] << 3);
            blue_data &= 0x00F8;

            working_data = (green_data | red_data | blue_data);
            working_data &= 0xFFFF;

            fwrite(&working_data, sizeof(uint16_t), 1, fileptr);

            index += mat->channel;
        }

        if (toggle_padding)
            fwrite(&padding, sizeof(uint16_t), 1, fileptr);

        index = 0;
    }

    fclose(fileptr);

cleanup_everything:
    deallocate_bmpcolorheader(color_ptr);
cleanup_info_header:
    deallocate_bmpinfoheader(info_ptr);
cleanup_file_header:
    deallocate_bmpfileheader(header_ptr);
}

#endif