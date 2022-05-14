#ifndef BITMAP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BMPFileHeader
{
    uint8_t file_type[2];
    uint8_t file_size[4];
    uint8_t reserved_1[2];
    uint8_t reserved_2[2];
    uint8_t offset_data[4];
};

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

struct BMPColorHeader
{
    uint8_t red_mask[4];
    uint8_t green_mask[4];
    uint8_t blue_mask[4];
    uint8_t alpha_mask[4];

    uint8_t color_space_type[4];
    uint8_t unused[64];
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
    *file_size = 0x0000008E;

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
    if (bmpFileHeaderPtr == NULL) return;
    free(bmpFileHeaderPtr);
}

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
    *width = 0x00000001;

    int32_t *height = (int32_t *)ptr->height;
    *height = 0x00000001;

    uint16_t *planes = (uint16_t *)ptr->planes;
    *planes = 0x0001;

    uint16_t *bit_count = (uint16_t *)ptr->bit_count;
    *bit_count = 0x0010;

    uint32_t *compression = (uint32_t *)ptr->compression;
    *compression = 0x00000003;

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
    if (bmpInfoHeaderPtr == NULL) return;
    free(bmpInfoHeaderPtr);
}

struct BMPColorHeader *allocate_bmpcolorheader()
{
    struct BMPColorHeader *ptr = (struct BMPColorHeader *)malloc(sizeof(struct BMPColorHeader));

    uint32_t* red_mask = (uint32_t*)ptr->red_mask;
    *red_mask = 0x0000F800;

    uint32_t* green_mask = (uint32_t*)ptr->green_mask;
    *green_mask = 0x000007E0;

    uint32_t* blue_mask = (uint32_t*)ptr->blue_mask;
    *blue_mask = 0x0000001F;

    uint32_t* alpha_mask = (uint32_t*)ptr->alpha_mask;
    *alpha_mask = 0x00000000;

    for(uint8_t index = 0; index < 64; index++) {
        ptr->unused[index] = 0x00;
    }

    return ptr;
}

void deallocate_bmpcolorheader(struct BMPColorHeader *bmpColorHeaderPtr)
{
    if (bmpColorHeaderPtr == NULL) return;
    free(bmpColorHeaderPtr);
}

#endif