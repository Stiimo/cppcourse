#include <progress_bar/progressbar.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cmath>

void ProgressBar::wrapForLoop(size_t total, const std::function<void(size_t i)> &loopBody) {
    ProgressBar pg(total);
    for (size_t i = 0; i < total; ++i, pg.iter()) {
        loopBody(i);
    }
}

ProgressBar::ProgressBar(size_t total) : m_total(total) {
    constexpr size_t textSize = 23;
    if (winsize size{}; ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) || size.ws_col <= 0) {
        std::cerr << "Failed to retrieve window size. Falling back to default window size: 100" << std::endl;
        m_lineSize = 100 - textSize;
    } else {
        m_lineSize = size.ws_col - textSize;
    }
    printProgress(0);
}

void ProgressBar::iter() {
    ++m_current;
    auto progress = static_cast<double>(m_current) / static_cast<double>(m_total);
    auto filledSize = std::lround(static_cast<double>(m_lineSize) * progress);
    std::cout << std::string(m_bytesPrinted, '\b');
    printProgress(filledSize);
}

void ProgressBar::printProgress(size_t filledSize) {
    std::ostringstream buf;
    buf << '[' << std::string(filledSize, '#') << std::string(m_lineSize - filledSize, ' ')
        << "] " << m_current << '/' << m_total;
    std::cout << buf.str();
    m_bytesPrinted = buf.str().size();
}

ProgressBar::~ProgressBar() {
    std::cout << std::string(m_bytesPrinted, '\b');
}
