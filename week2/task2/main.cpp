#include "timer.h"
#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include <progress_bar/progressbar.h>

std::vector<int> genValues(size_t n) {
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

void oneSortTest(std::array<uint64_t, 5> &times) {
    constexpr size_t n = 100000;
    std::vector<int> v = genValues(n);
    std::array<int, n> a{};
    std::deque<int> d;
    std::list<int> dl;
    std::forward_list<int> fl;
    for (size_t i = 0; i < n; ++i) {
        a[i] = v[i];
        d.push_back(v[i]);
        dl.push_back(v[i]);
        fl.push_front(v[n - i - 1]);
    }
    // Vector
    {
        Timer t;
        std::sort(v.begin(), v.end());
        times[0] += t.elapsed();
    }
    // Array
    {
        Timer t;
        std::sort(a.begin(), a.end());
        times[1] += t.elapsed();
    }
    // Deque
    {
        Timer t;
        std::sort(d.begin(), d.end());
        times[2] += t.elapsed();
    }
    // List
    {
        Timer t;
        dl.sort();
        times[3] += t.elapsed();
    }
    // Forward list
    {
        Timer t;
        fl.sort();
        times[4] += t.elapsed();
    }
}

void sortTest() {
    std::array<uint64_t, 5> times{};
    constexpr size_t iters = 100000;
    ProgressBar::wrapForLoop(iters, [&times](size_t) { oneSortTest(times); });
    std::array<double, 5> avgTimes{};
    std::transform(times.begin(), times.end(), avgTimes.begin(), [](uint64_t x) { return x * 1.0 / iters; });
    std::cout << "Vector: " << avgTimes[0] << std::endl;
    std::cout << "Array: " << avgTimes[1] << std::endl;
    std::cout << "Deque: " << avgTimes[2] << std::endl;
    std::cout << "List: " << avgTimes[3] << std::endl;
    std::cout << "Forward list: " << avgTimes[4] << std::endl;
}

/*
Среднее по 100к элементам на 100к запусков:
Vector: 4730,27 мкс
Array: 4717,04 мкс
Deque: 5779,28 мкс
List: 19088,90 мкс
Forward list: 73397,20 мкс
*/

int main() {
    sortTest();
    return 0;
}
