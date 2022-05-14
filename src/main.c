#include <stdio.h>
#include "matrix.h"
#include "bitmap.h"

int main()
{
    printf("Hello world!\n");

    struct matrix *mat = allocate_matrix(JPG_FORMAT, 3, 3);
    if (mat == NULL)
    {
        printf("Unable to allocate matrix.\n");
        return 0;
    }
    write_rgb565_pixel(0xFF, 0xFF, 0xFF, mat, 0, 0);
    write_rgb565_pixel(0xFF, 0xFF, 0xFF, mat, 1, 1);
    write_rgb565_pixel(0xFF, 0xFF, 0xFF, mat, 2, 2);

    print_matrix(mat);

    const char* test_path = "test.bmp";

    struct BMPFileHeader* header_ptr = allocate_bmpfileheader();
    struct BMPInfoHeader* info_ptr = allocate_bmpinfoheader();
    struct BMPColorHeader* color_ptr = allocate_bmpcolorheader();

    if(header_ptr == NULL) {
        printf("Unable to allocate BMPFileHeader.\n");
        return -1;
    }

    if(info_ptr == NULL) {
        printf("Unable to allocate BMPInfoHeader.\n");
        return -1;
    }

    if(color_ptr == NULL) {
        printf("Unable to allocate BMPColorHeader.\n");
        return -1;
    }

    FILE *fileptr = fopen(test_path, "wb");
    if(fileptr == NULL) {
        printf("Unable to open %s for binary writing.\n", test_path);
        return -1;
    }

    fwrite(header_ptr, sizeof(struct BMPFileHeader), 1, fileptr);
    fwrite(info_ptr, sizeof(struct BMPInfoHeader), 1, fileptr);
    fwrite(color_ptr, sizeof(struct BMPColorHeader), 1, fileptr);

    fclose(fileptr);

    deallocate_bmpfileheader(header_ptr);
    deallocate_bmpinfoheader(info_ptr);
    deallocate_bmpcolorheader(color_ptr);
}