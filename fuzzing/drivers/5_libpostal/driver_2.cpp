#include "../../projectFiles/5_libpostal/src/libpostal.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char ** argv) {

    if (argc != 2) {
        printf("Usage: %s <input_file>", argv[0]);
        exit(1);
    }

    std::ifstream file(argv[1], std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    size_t n;

    libpostal_setup();
    libpostal_setup_language_classifier();
    libpostal_expand_address((char*) &input[0], libpostal_get_default_options(), &n);

    return 0;
}