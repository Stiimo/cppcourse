#include <fstream>
#include "preprocessor.h"

int main() {
    std::ifstream fin("test.txt");
    std::ofstream fout("/tmp/result.cpp");
    Preprocessor p;
    p.process(fin, fout);
    return 0;
}
