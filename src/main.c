#include <stdio.h>
#include "matrix.h"
#include "bitmap.h"

int main()
{
    struct matrix *mat = allocate_matrix(24, 24);
    if (mat == NULL)
    {
        printf("Unable to allocate matrix.\n");
        return 0;
    }

    write_rgb565_pixel_rgb(0xFF, 0x00, 0x00, mat, 0, 0);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 1, 1);
    write_rgb565_pixel_rgb(0x00, 0x00, 0xFF, mat, 2, 2);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 3, 3);
    write_rgb565_pixel_rgb(0xFF, 0x00, 0x00, mat, 4, 4);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 5, 5);
    write_rgb565_pixel_rgb(0x00, 0x00, 0xFF, mat, 6, 6);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 7, 7);
    write_rgb565_pixel_rgb(0xFF, 0x00, 0x00, mat, 8, 8);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 9, 9);
    write_rgb565_pixel_rgb(0x00, 0x00, 0xFF, mat, 10, 10);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 11, 11);
    write_rgb565_pixel_rgb(0xFF, 0x00, 0x00, mat, 12, 12);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 13, 13);
    write_rgb565_pixel_rgb(0x00, 0x00, 0xFF, mat, 14, 14);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 15, 15);
    write_rgb565_pixel_rgb(0xFF, 0x00, 0x00, mat, 16, 16);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 17, 17);
    write_rgb565_pixel_rgb(0x00, 0x00, 0xFF, mat, 18, 16);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 19, 15);
    write_rgb565_pixel_rgb(0xFF, 0x00, 0x00, mat, 20, 14);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 21, 13);
    write_rgb565_pixel_rgb(0x00, 0x00, 0xFF, mat, 22, 12);
    write_rgb565_pixel_rgb(0x00, 0xFF, 0x00, mat, 23, 11);

    const char* test_path = "application_2.bmp";

    write_rgb565_bmpfile(test_path, mat);

    deallocate_matrix(mat);
}