#include <iostream>
#include <vector>

using vector_t = std::vector<char>;

void printVectorSizeInfo(const vector_t &v)
{
    std::cout << "Size: " << v.size() << " Capacity: " << v.capacity() << std::endl;
}

void memMultiplierCoef()
{
    vector_t v;
    printVectorSizeInfo(v);
    for (int i = 0; i < 20; ++i) {
        v.push_back(' ');
        printVectorSizeInfo(v);
    }
}

void reserveTest()
{
    for (const auto &s : {3, 6, 8, 10, 15}) {
        vector_t v;
        v.reserve(s);
        printVectorSizeInfo(v);
        for (int i = 0; i < 20; ++i) {
            v.push_back(' ');
            printVectorSizeInfo(v);
        }
        std::cout << std::endl;
    }
}

void insufficientMemoryTest()
{
    vector_t v(12500000000, ' ');
    printVectorSizeInfo(v);
    v.push_back(' ');
    printVectorSizeInfo(v);
}

int main()
{
    //    memMultiplierCoef();
    //    reserveTest();
    insufficientMemoryTest();
    return 0;
}
