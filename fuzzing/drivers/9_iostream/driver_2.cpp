#include <fstream>
#include <iostream>

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: %s <input_file>", argv[0]);
    }

    std::string a;
    int b;
    char c;
    char d[100];
    std::string e;

    std::ifstream inf(argv[1]);

    std::getline(inf, e);
    inf >> a >> b >> c;
    inf.getline(d, sizeof(d));

    return 0;
}