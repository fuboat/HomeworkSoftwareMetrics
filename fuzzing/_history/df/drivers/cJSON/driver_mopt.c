#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "cJSON.h"

#define MAX_INPUT_SIZE 4096

int main(int argc, char* argv[]) {
    int input_fd = 0;
    unsigned char input_buf[MAX_INPUT_SIZE];
    ssize_t input_size;

    if (argc != 2) {
        printf("Usage: afl_driver <input_file>\n");
        return 1;
    }

    const char* input_file = argv[1];

    // Open the input file
    input_fd = open(input_file, O_RDONLY);
    if (input_fd == -1) {
        perror("Failed to open input file");
        return 1;
    }

    // Read input file
    input_size = read(input_fd, input_buf, MAX_INPUT_SIZE - 1);
    if (input_size == -1) {
        perror("Failed to read input file");
        return 1;
    }
    input_buf[input_size] = '\0'; // Null-terminate the input

    // Create cJSON object from input
    cJSON* root = cJSON_Parse(input_buf);
    if (root == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error before: %s\n", error_ptr);
        }
        return 1;
    }

    // Perform operations on cJSON object
    // Example: Print the JSON structure
    char* json_string = cJSON_Print(root);
    printf("%s\n", json_string);
    free(json_string);

    // Clean up cJSON object
    cJSON_Delete(root);

    // Close the input file
    close(input_fd);

    return 0;
}

