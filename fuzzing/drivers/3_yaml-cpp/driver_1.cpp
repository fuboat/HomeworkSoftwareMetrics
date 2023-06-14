#include "../../projectFiles/3_yaml-cpp/include/yaml-cpp/yaml.h"

#include <iostream>
#include <sstream>

int main() {
    std::string input;
    input.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());

    try {
    YAML::Load(input);
    YAML::LoadAll(input);
    } catch (...) {
        
    }

    return 0;
}
