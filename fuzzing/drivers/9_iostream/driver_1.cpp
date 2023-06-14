#include <iostream>

int main() {

    std::string a;
    int b;
    char c;
    char d[100];
    std::string e;

    std::getline(std::cin, e);
    std::cin >> a >> b >> c;
    std::cin.getline(d, sizeof(d));

    return 0;
}