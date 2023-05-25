#include <iostream>
#include <fstream>
#include <libqalculate/qalculate.h>

#define MAX_INPUT_SIZE 4096

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: afl_driver <input_file>\n";
        return 1;
    }

    const char* input_file = argv[1];

    // Open the input file
    std::ifstream file(input_file);
    if (!file) {
        std::cerr << "Failed to open input file\n";
        return 1;
    }
    char expression[MAX_INPUT_SIZE];
    // Initialize the calculator
    new Calculator(false);

    while (file.getline(expression, MAX_INPUT_SIZE)) {
        EvaluationOptions eo;
        MathStructure result;
        CALCULATOR->calculate(&result, CALCULATOR->unlocalizeExpression(expression), 2000, eo);
    }
    // Close the input file
    file.close();
    return 0;
}
