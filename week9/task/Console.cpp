#include "Console.h"
#include "types.h"
#include <iostream>
#include <termios.h>

void Console::getString(std::string &s) {
    while (!m_eof) {
        char c;
        std::cin >> c;
        // 4 is EOT in ASCII
        if (c == 4) {
            std::cout << std::endl;
            m_eof = true;
        } else if (c == '\n') {
            std::cout << c;
            break;
        } else if (c == 127) {
            if (!m_buffer.empty()) {
                m_buffer.pop_back();
            }
            std::cout << "\b \b";
        } else {
            m_buffer.push_back(c);
            std::cout << c;
        }
    }

    s = m_buffer;
    m_buffer.clear();
}

void Console::putString(const std::string &s) {
    std::cout << std::string(m_buffer.size(), '\b') << s << '\n' << m_buffer;
    std::cout.flush();
}

Console *Console::instance() {
    static Console self;
    return &self;
}

void Console::putString(const MsgData &data) {
    std::cout << std::string(m_buffer.size(), '\b') << data << '\n' << m_buffer;
    std::cout.flush();
}

bool Console::good() const {
    return !m_eof;
}

Console::Console() {
    oldTio = termiosPtr(new termios(), [](termios *tio) {
        if (!tio) {
            return;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, tio);
    });
    tcgetattr(STDIN_FILENO, oldTio.get());
    auto newTio = *oldTio;
    newTio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTio);
    noskipws(std::cin);
}
