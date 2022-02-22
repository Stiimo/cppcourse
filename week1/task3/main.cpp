#include <timer/timer.hpp>
#include <iostream>

// Исходный код таймера в utils/timer/include/timer
int main() {
    Timer<std::chrono::microseconds> t("MicroTimer", false);
    t.start();
    double x = 0.0;
    for (int i = 0; i < 1000000; ++i) {
        x += 1.25;
    }
    t.stop();
    std::cout << x << std::endl;
    std::cout << t << std::endl;
    return 0;
}
