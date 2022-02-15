#include "timer.h"
#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

std::vector<int> genValues(size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    std::vector<int> v;
    v.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        v.push_back(dist(gen));
    }
    return v;
}

void sortTest()
{
    constexpr size_t n = 1000000;
    std::vector<int> v = genValues(n);
    std::array<int, n> a;
    std::deque<int> d;
    std::list<int> dl;
    std::forward_list<int> fl;
    for (size_t i = 0; i < n; ++i) {
        a[i] = v[i];
        d.push_back(v[i]);
        dl.push_back(v[i]);
        fl.push_front(v[n - i - 1]);
    }
    std::cout << "Vector: ";
    {
        Timer t;
        std::sort(v.begin(), v.end());
    }
    std::cout << "Array: ";
    {
        Timer t;
        std::sort(a.begin(), a.end());
    }
    std::cout << "Deque: ";
    {
        Timer t;
        std::sort(d.begin(), d.end());
    }
    std::cout << "List: ";
    {
        Timer t;
        dl.sort();
    }
    std::cout << "Forward list: ";
    {
        Timer t;
        fl.sort();
    }
}

/*
Для 1м элементов:
Vector: 52637 мкс
Array: 57536 мкс
Deque: 68985 мкс
List: 275424 мкс
Forward list: 585439 мкс
*/

int main()
{
    sortTest();
    return 0;
}
