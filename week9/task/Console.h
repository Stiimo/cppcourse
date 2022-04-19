#pragma once

#include <string>
#include <memory>
#include <functional>

struct MsgData;

class termios;

class Console {
public:
    void getString(std::string &s);

    void putString(const std::string &s);

    void putString(const MsgData &data);

    [[nodiscard]] bool good() const;

    static Console *instance();

private:
    explicit Console();

    using termiosPtr = std::unique_ptr<termios, std::function<void(termios *)>>;

    std::string m_buffer{};
    bool m_eof{false};
    termiosPtr oldTio;
};
