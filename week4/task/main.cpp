#include <iostream>
#include <random>
#include <iterator>
#include <vector>
#include <numeric>

void printTask(int task) {
    std::cout << "Task " << task << ": ";
}

void print(int task, const std::vector<int> &v) {
    printTask(task);
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    std::vector<int> v(10);
    int task = 0;
    // task 1
    std::iota(v.begin(), v.end(), 1);
    print(++task, v);
    // task 2
    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(v));
    print(++task, v);
    // task 3
    std::random_device d;
    std::mt19937 gen(d());
    std::shuffle(v.begin(), v.end(), gen);
    print(++task, v);
    // task 4
    std::sort(v.begin(), v.end());
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end());
    v.shrink_to_fit();
    print(++task, v);
    // task 5
    printTask(++task);
    std::cout << "# of odd values: " << std::count_if(v.begin(), v.end(), [](int x) { return x % 2; }) << std::endl;
    // task 6
    const auto[min, max] = std::minmax_element(v.begin(), v.end());
    printTask(++task);
    std::cout << "min: " << *min << " max: " << *max << std::endl;
    // task 7
    auto it = std::find_if(v.begin(), v.end(), [](int x) {
        if (x == 1) {
            return false;
        }
        for (int i = 2; i <= std::sqrt(x); ++i) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    });
    printTask(++task);
    std::cout << "prime number: " << *it << std::endl;
    // task 8
    std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * x; });
    print(++task, v);
    // task 9
    std::vector<int> v2(v.size());
    std::uniform_int_distribution intDist(-10, 10);
    std::generate(v2.begin(), v2.end(), [&intDist, &gen]() { return intDist(gen); });
    print(++task, v2);
    // task 10
    printTask(++task);
    std::cout << std::accumulate(v2.begin(), v2.end(), 0) << std::endl;
    // task 11
    std::fill_n(v2.begin(), 3, 1);
    print(++task, v2);
    // task 12
    std::vector<int> v3(v.size());
    std::transform(v.begin(), v.end(), v2.begin(), v3.begin(), std::minus<>());
    print(++task, v3);
    // task 13
    std::transform(v3.begin(), v3.end(), v3.begin(), [](int x) { return x < 0 ? 0 : x; });
    print(++task, v3);
    // task 14
    auto t14It = std::remove_if(v3.begin(), v3.end(), [](int x) { return x == 0; });
    v3.erase(t14It, v3.end());
    v3.shrink_to_fit();
    print(++task, v3);
    // task 15
    std::reverse(v3.begin(), v3.end());
    print(++task, v3);
    // task 16
    // TODO: top 3 max
    std::make_heap(v3.begin(), v3.end());
    printTask(++task);
    for (int i = 0; i < 3; ++i) {
        std::pop_heap(v3.begin(), v3.end());
        std::cout << v3.back() << ' ';
        v3.pop_back();
    }
    std::cout << std::endl;
    // task 17
    std::sort(v.begin(), v.end());
    std::sort(v2.begin(), v2.end());
    print(++task, v);
    print(task, v2);
    // task 18
    std::vector<int> v4(v.size() + v2.size());
    last = std::set_union(v.begin(), v.end(), v2.begin(), v2.end(), v4.begin());
    v4.erase(last, v4.end());
    print(++task, v4);
    // task 19
    auto lower = std::lower_bound(v4.begin(), v4.end(), 1);
    auto upper = std::upper_bound(v4.begin(), v4.end(), 1);
    printTask(++task);
    std::cout << '[' << lower - v4.begin() << ", " << upper - v4.begin() << ')' << std::endl;
    return 0;
}
