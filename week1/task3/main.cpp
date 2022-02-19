#include "timer.h"
#include <iostream>

int main()
{
    Timer<std::chrono::microseconds> t;
    t.start();
    {
        double x = 0.0;
        for (int i = 0; i < 1000000; ++i) {
            x += 1.25;
        }
    }
    t.stop();
    std::cout << t;
    return 0;
}
