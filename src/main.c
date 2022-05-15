#include <stdio.h>
#include "matrix.h"
#include "bitmap.h"

int main()
{
    printf("Hello world!\n");

    struct matrix *mat = allocate_matrix(JPG_FORMAT, 1, 1);
    if (mat == NULL)
    {
        printf("Unable to allocate matrix.\n");
        return 0;
    }
    // write_rgb565_pixel_code(0x07ff, mat, 0, 0);
    // write_rgb565_pixel_rgb(0xFF, 0x00, 0x00, mat, 0, 0);
    write_rgb565_pixel_rgb(0xFF, 0xFF, 0x00, mat, 0, 0);

    // write_rgb565_pixel_rgb(0xFF, 0xFF, 0xFF, mat, 1, 1);
    // write_rgb565_pixel_rgb(0xFF, 0xFF, 0xFF, mat, 1, 0);

    print_matrix(mat);

    const char* test_path = "application.bmp";

    write_rgb565_bmpfile(test_path, mat);

    deallocate_matrix(mat);
}