#pragma once

#include <unordered_map>

class Transliterator {
public:
    Transliterator();

    std::u32string convert(char32_t c) const;

    std::u32string convert(const std::u32string &text) const;

private:
    std::unordered_map<char32_t, std::u32string> m_conversionTable;
};
