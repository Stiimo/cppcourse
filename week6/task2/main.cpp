#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream input("w6_t2_input");
    std::string line;
    std::getline(input, line);
    size_t lineSize = line.size() + 1;
    input.seekg(0);
    int lineNum;
    std::cin >> lineNum;
    input.seekg(lineNum * static_cast<int>(lineSize));
    std::getline(input, line);
    if (input.good()) {
        std::cout << line << std::endl;
    } else {
        std::cout << "There are no such line" << std::endl;
    }
    return 0;
}
