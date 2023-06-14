#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "../../projectFiles/6_cJSON/cJSON.h"

#define MAX_INPUT_SIZE 4096

int main() {
    int input_fd = 0;
    char input_buf[MAX_INPUT_SIZE];
    ssize_t input_size;

    // Read input file
    input_size = read(STDIN_FILENO, input_buf, MAX_INPUT_SIZE - 1);
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