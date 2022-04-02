#include <algorithm>
#include <future>
#include <iostream>
#include <random>
#include <iterator>

template<typename InputIt, typename UnaryFunction>
void for_each(InputIt first, InputIt last, UnaryFunction f) {
    constexpr long min_size = 25;
    long dist = std::distance(first, last);
    if (dist < min_size) {
        std::for_each(first, last, f);
        return;
    }
    auto mid = first;
    std::advance(mid, dist / 2);
    auto res = std::async(::for_each<InputIt, UnaryFunction>, first, mid, f);
    ::for_each(mid, last, f);
    res.wait();
}

void gen(std::vector<int> &v) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100000);
    ::for_each(v.begin(), v.end(), [&dist, &gen](int &x) { x = dist(gen); });
}

int main() {
    size_t size;
    std::cin >> size;
    std::vector<int> v(size, 0);
    gen(v);
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, "\n"));
    return 0;
}