#include <iostream>
#include <regex>
#include <iterator>

int main() {
    std::regex pattern(R"([[:alnum:]](?:[\w\.\-\+]{0,62}[[:alnum:]])?@[\w\-]+(?:\.[\w\-]+)*\.[[:alnum:]]+)");
    std::string text;
    std::cin.unsetf(std::ios::skipws);
    std::copy(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), std::back_inserter(text));
    for (auto it = std::sregex_iterator(text.begin(), text.end(), pattern); it != std::sregex_iterator(); ++it) {
        std::cout << it->str() << std::endl;
    }
    return 0;
}
