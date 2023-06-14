#include <iostream>
#include <fstream>
#include "../../projectFiles/X_libqalculate/libqalculate/qalculate.h"

#define MAX_INPUT_SIZE 4096

int main() {
    // Open the input file
    auto & file = std::cin;
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
    return 0;
}
