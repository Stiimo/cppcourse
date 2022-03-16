#include <iostream>
#include <iterator>
#include <string>
#include <boost/locale.hpp>
#include "transliterator.h"

int main() {
    std::string text;
    std::copy(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), std::back_inserter(text));
    std::u32string u32text = boost::locale::conv::utf_to_utf<char32_t>(text);
    std::u32string u32transliterated;
    try {
        Transliterator t;
        u32transliterated = t.convert(u32text);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    std::string transliterated = boost::locale::conv::utf_to_utf<char>(u32transliterated);
    std::cout << transliterated;
    return 0;
}
