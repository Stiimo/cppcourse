#pragma once

#include <chrono>
#include <iostream>

class Timer {
    using clock_t = std::chrono::steady_clock;
    using duration_t = std::chrono::microseconds;
    using time_point_t = clock_t::time_point;

public:
    Timer() = default;

    ~Timer() = default;

    Timer(const Timer &other) = delete;

    Timer &operator=(const Timer &other) = delete;

    [[nodiscard]] uint64_t elapsed() const {
        return std::chrono::duration_cast<duration_t>(clock_t::now() - m_begin).count();
    }

private:
    time_point_t m_begin{clock_t::now()};
};
