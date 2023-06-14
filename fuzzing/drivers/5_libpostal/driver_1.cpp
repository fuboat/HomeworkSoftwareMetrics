#include "../../projectFiles/5_libpostal/src/libpostal.h"

#include <iostream>
#include <string>

int main() {
    std::string input;
    input.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());

    size_t n;

    libpostal_setup();
    libpostal_setup_language_classifier();
    libpostal_expand_address((char*) &input[0], libpostal_get_default_options(), &n);

    return 0;
}