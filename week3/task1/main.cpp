#include <iostream>
#include <progress_bar/progressbar.h>
#include <timer/timer.hpp>
#include <numeric>
#include <random>
#include <vector>
#include <set>
#include <unordered_set>

std::unordered_set<int> genUniqueValues(size_t n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    std::unordered_set<int> s;
    while (s.size() != n) {
        s.insert(dist(gen));
    }
    return s;
}

void oneSortTest(std::array<uint64_t, 2> &times) {
    constexpr size_t n = 100000;
    auto values = genUniqueValues(n);
    // Vector
    {
        std::vector<int> v;
        v.reserve(n);
        Timer<std::chrono::microseconds> t(true);
        t.start();
        for (auto value: values) {
            v.push_back(value);
        }
        std::sort(v.begin(), v.end());
        t.stop();
        times[0] += t.elapsed()->count();
    }
    // Set
    {
        std::set<int> s;
        Timer<std::chrono::microseconds> t(true);
        t.start();
        for (auto value: values) {
            s.insert(value);
        }
        t.stop();
        times[1] += t.elapsed()->count();
    }
}

void sortTest() {
    std::array<uint64_t, 2> times{};
    constexpr size_t iters = 100000;
    {
        ProgressBar::wrapForLoop(iters, [&times](size_t) { oneSortTest(times); });
    }
    std::array<double, 2> avgTimes{};
    std::transform(times.begin(), times.end(), avgTimes.begin(),
                   [](uint64_t x) { return static_cast<double>(x) / iters; });
    std::cout << "Vector: " << avgTimes[0] << std::endl;
    std::cout << "Set: " << avgTimes[1] << std::endl;
}

/*
Среднее по 100к элементам на 100к запусков:
Vector: 6890.94 мкс
Set: 30603.40 мкс
*/

int main() {
    sortTest();
    return 0;
}
