#include "../../projectFiles/3_yaml-cpp/include/yaml-cpp/yaml.h"

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: %s <inputfile>", argv[0]);
        exit(1);
    }

    try {
    YAML::LoadFile(argv[1]);
    YAML::LoadAllFromFile(argv[1]);
    } catch (...) {
        
    }

    return 0;
}
