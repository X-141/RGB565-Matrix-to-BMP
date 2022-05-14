#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "matrix.h"
#include "printf.h"

int8_t zero_matrix(struct matrix *mat)
{
    if (!mat)
    {
        printf("zero_matrix: data_ptr is NULL.\n");
        return ERROR;
    }

    if (!(mat->mem))
    {
        printf("zero_matrix: data_ptr underlying data is NULL.\n");
        return ERROR;
    }

    uint8_t *mem = mat->mem;
    for (uint32_t index = 0; index < mat->size; index++)
    {
        mem[index] = 0;
    }

    return 0;
}

struct matrix *allocate_matrix(uint8_t type, uint16_t horizontal_dim, uint16_t vertical_dim)
{
    struct matrix *mat = (struct matrix *)malloc(sizeof(struct matrix));
    if (!mat)
    {
        printf("allocate_matrix: failed to allocate matrix_info struct.\n");
        return NULL;
    }

    mat->horizontal = horizontal_dim;
    mat->vertical = vertical_dim;

    switch (type)
    {
    case JPG_FORMAT:
        mat->channel = JPG_FORMAT_CHANNELS;
        break;
    default:
        printf("allocate_matrix: Type indicated is not known.\n");
        return NULL;
    }

    mat->size = mat->horizontal * mat->vertical * mat->channel;
    mat->mem = (uint8_t *)malloc(sizeof(uint8_t) * (mat->size));

    if (zero_matrix(mat) < 0)
    {
        printf("allocate_matrix: unable to zero matrix.\n");
        return NULL;
    }

    return mat;
}

void deallocate_matrix(struct matrix *mat)
{

    if (mat != NULL && mat->mem)
    {
        free(mat->mem);
        mat->horizontal = -1;
        mat->vertical = -1;
        mat->channel = -1;
        mat->size = -1;

        free(mat);
    }
}

uint8_t print_matrix(struct matrix *mat)
{
    if (mat == NULL)
    {
        printf("print_matrix: mat passed is NULL.\n");
        return ERROR;
    }

    uint16_t x_row, y_column, x_offset, y_offset;
    uint8_t z_channel;
    printf("[\n");
    for (x_row = 0; x_row < mat->vertical; x_row++)
    {
        x_offset = x_row * mat->horizontal * mat->channel;
        printf("[");
        for (y_column = 0; y_column < mat->horizontal; y_column++)
        {
            y_offset = y_column * mat->channel;
            printf("[");
            for (z_channel = 0; z_channel < mat->channel; z_channel++)
            {
                printf("%3d", mat->mem[x_offset + y_offset + z_channel]);
            }
            printf("  ]");
        }
        printf("]\n");
    }
    printf("]\n");

    return 0;
}

void write_rgb565_pixel(uint8_t red, uint8_t green, uint8_t blue,
                        struct matrix *mat, uint16_t row, uint16_t column)
{
    if (mat == NULL)
    {
        printf("write_rgb565_pixel: mat passed is NULL.\n");
        return;
    }

    uint32_t offset = row * mat->vertical * mat->channel + column * mat->channel;

    if (offset >= mat->size)
    {
        printf("write_color: computed offset value to index underlying matrix is greater than actual size. Likely error in my code.\n");
        return;
    }

    mat->mem[offset + 0] = red & 0x1F;
    mat->mem[offset + 1] = green & 0x3F;
    mat->mem[offset + 2] = blue & 0x1F;
}