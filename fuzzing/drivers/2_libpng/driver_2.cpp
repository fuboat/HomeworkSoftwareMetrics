#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "../../projectFiles/2_libpng/png.h"

#define MAX_INPUT_SIZE 8192

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: afl_driver <input_file>\n");
        return 1;
    }

    const char* file_name = argv[1];
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        printf("File Open Error!");
        return 1;
    }
    unsigned char header[1024];
    fread(header, 1, 8, fp);
    int is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png) {
        printf("File Invalid!");
        return 1;
    }

    // Initialize libpng structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        printf("Failed to create PNG read struct\n");
        return 1;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        printf("Failed to create PNG info struct\n");
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return 1;
    }
    // Set error handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        printf("Error during PNG processing\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return 1;
    }

    // Set input source
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    // Read the PNG header
    png_read_info(png_ptr, info_ptr);

    // Perform operations on the PNG file
    // Example: Print the PNG image dimensions
    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
    printf("Image dimensions: %d x %d\n", width, height);

    // Clean up libpng structures
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    // Close the input file
    fclose(fp);

    return 0;
}