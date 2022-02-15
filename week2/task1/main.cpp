#include <iostream>
#include <vector>

using vector_t = std::vector<char>;

void printVectorSizeInfo(const vector_t &v)
{
    std::cout << "Size: " << v.size() << " Capacity: " << v.capacity() << std::endl;
}

// Коэффициент изменения емкости вектора - х2
void memMultiplierCoef()
{
    std::cout << "Memory multiply coefficient test" << std::endl;
    vector_t v;
    printVectorSizeInfo(v);
    for (int i = 0; i < 20; ++i) {
        v.push_back(' ');
        printVectorSizeInfo(v);
    }
}

// Тут остается тот же коээфициент
void reserveTest()
{
    std::cout << "Reserv test" << std::endl;
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

// Исключение std::bad_alloc
void insufficientMemoryTest()
{
    std::cout << "Insufficient memory test" << std::endl;
    vector_t v(12500000000, ' ');
    printVectorSizeInfo(v);
    v.push_back(' ');
    printVectorSizeInfo(v);
}

int main()
{
    memMultiplierCoef();
    reserveTest();
    try {
        insufficientMemoryTest();
    } catch (const std::bad_alloc& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
