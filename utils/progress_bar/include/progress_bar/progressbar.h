#pragma once

#include <functional>
#include <cstddef>

class ProgressBar {
public:
    static void wrapForLoop(size_t total, const std::function<void(size_t i)> &loopBody);

    ~ProgressBar();

    ProgressBar(const ProgressBar &other) = delete;

    ProgressBar &operator=(const ProgressBar &other) = delete;

private:
    explicit ProgressBar(size_t total);

    void iter();

    void printProgress(size_t filledSize);

    size_t m_bytesPrinted{0};
    size_t m_current{0};
    size_t m_total;
    size_t m_lineSize;
};
