#include <stdio.h>
#include "matrix.h"
#include "bitmap.h"

int main()
{
    struct matrix *mat = allocate_matrix(320, 240);
    if (mat == NULL)
    {
        printf("Unable to allocate matrix.\n\tGoing to cleanup.\n");
        return 0;
    }

    bool success = read_binary_file(mat, "../VIDEO001.RAW");
    if (!success)
    {
        printf("Failed to read in binary file into matrix.\n\tGoing to cleanup.\n");
        goto cleanup;
    }

    draw_rectangle(mat, 0x8710, 1, 44, 44, 200, 200);

    print_matrix(mat);

    const char *test_path = "application_13.bmp";

    write_rgb565_bmpfile(test_path, mat);

cleanup:
    deallocate_matrix(mat);
}