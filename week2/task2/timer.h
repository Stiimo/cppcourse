#pragma once
#include <chrono>
#include <iostream>
#include <optional>

class Timer
{
    using clock_t = std::chrono::steady_clock;
    using duration_t = std::chrono::microseconds;
    using time_point_t = clock_t::time_point;

public:
    Timer() = default;

    ~Timer()
    {
        try {
            std::cout << std::chrono::duration_cast<duration_t>(clock_t::now() - m_begin).count() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Unhandled exception: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unhandled unknown exception" << std::endl;
        }
    }

    Timer(const Timer& other) = delete;
    Timer& operator=(const Timer& other) = delete;

private:
    time_point_t m_begin { clock_t::now() };
};
