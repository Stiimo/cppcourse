#include "transliterator.h"
#include <fstream>
#include <boost/locale.hpp>

Transliterator::Transliterator() {
    std::ifstream table("table.tsv");
    if (!table.is_open()) {
        throw std::runtime_error("failed to open conversion table");
    }
    while (!table.eof()) {
        std::string line;
        std::getline(table, line);
        if (line.empty()) { continue; }
        auto u32line = boost::locale::conv::utf_to_utf<char32_t>(line);
        auto key = u32line[0];
        auto value = u32line.substr(2);
        m_conversionTable[key] = value;
    }
}

std::u32string Transliterator::convert(char32_t c) const {
    if (m_conversionTable.contains(c)) {
        return m_conversionTable.at(c);
    }
    return {c};
}

std::u32string Transliterator::convert(const std::u32string &text) const {
    std::u32string result;
    for (auto c: text) {
        result += convert(c);
    }
    return result;
}
