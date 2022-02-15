#pragma once
#include <chrono>
#include <iostream>
#include <optional>

class Timer
{
    using clock_t = std::chrono::steady_clock;
    using duration_t = std::chrono::milliseconds;
    using time_point_t = clock_t::time_point;

public:
    Timer() = default;

    ~Timer()
    {
        try {
            std::cout << std::chrono::duration_cast<duration_t>(clock_t::now() - m_begin).count() << std::endl;
        } catch (...) {
        }
    }

    Timer(const Timer& other) = delete;
    Timer& operator=(const Timer& other) = delete;

    //    void start()
    //    {
    //        if (!m_isActive) {
    //            m_isActive = true;
    //            m_begin = clock_t::now();
    //        }
    //    }

    //    void stop()
    //    {
    //        if (m_isActive) {
    //            m_totalDuration += std::chrono::duration_cast<duration_t>(clock_t::now() - m_begin);
    //            m_isActive = false;
    //        }
    //    }

    //    auto isActive() const noexcept { return m_isActive; }

    //    std::optional<uint64_t> elapsed() const
    //    {
    //        return isActive() ? std::optional<uint64_t>()
    //                          : static_cast<uint64_t>(m_totalDuration.count());
    //    }

private:
    time_point_t m_begin { clock_t::now() };
    //    duration_t m_totalDuration{0};
    //    bool m_isActive{false};
};
