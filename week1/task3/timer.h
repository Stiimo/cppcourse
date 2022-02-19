#pragma once
#include <chrono>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>

namespace units_text {
template <typename Duration>
std::string units();

template <>
std::string units<std::chrono::nanoseconds>()
{
    return "ns";
}

template <>
std::string units<std::chrono::microseconds>()
{
    return "us";
}

template <>
std::string units<std::chrono::milliseconds>()
{
    return "ms";
}

template <>
std::string units<std::chrono::seconds>()
{
    return "s";
}

template <>
std::string units<std::chrono::minutes>()
{
    return "m";
}

template <>
std::string units<std::chrono::hours>()
{
    return "h";
}

} // ns units_text

template <typename Duration>
class Timer {
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;

public:
    Timer() = default;

    explicit Timer(const std::string& name)
        : m_name(name)
    {
    }

    Timer(const Timer& other) = delete;
    Timer& operator=(const Timer& other) = delete;

    ~Timer() noexcept
    {
        try {
            stop();
            std::cout << *this << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Unhandled exception during " << m_name << " timer destruction: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unhandled unknown exception during " << m_name << " timer destruction" << std::endl;
        }
    }

    bool isActive() const noexcept { return m_isActive; }

    std::optional<Duration> elapsed() const noexcept
    {
        return isActive() ? std::optional<Duration>() : m_totalDuration;
    }

    std::string name() const noexcept
    {
        return m_name;
    }

    void start() noexcept
    {
        if (isActive()) {
            return;
        }
        m_isActive = true;
        m_begin = clock_t::now();
    }

    void stop()
    {
        if (!isActive()) {
            return;
        }
        m_totalDuration += std::chrono::duration_cast<Duration>(clock_t::now() - m_begin);
        m_isActive = false;
    }

    std::string units() const noexcept { return units_text::units<Duration>(); }

private:
    Duration m_totalDuration { 0 };
    time_point_t m_begin {};
    bool m_isActive { false };
    std::string m_name { "Timer" };
};

template <typename Duration>
std::ostream& operator<<(std::ostream& s, const Timer<Duration>& t)
{
    auto name = t.name();
    auto elapsed = t.elapsed();
    if (elapsed.has_value()) {
        s << name << ": " << elapsed.value().count() << ' ' << t.units();
    } else {
        s << name << " is running now";
    }
    return s;
}
