#include <iostream>
#include <regex>
#include <iterator>

int main() {
    std::regex pattern(
            R"(\d{4}\.(?:0\d|1[0-2])\.(?:(?<=(?:01|03|05|07|08|10|12)\.)(?:[0-2]\d|3[0-1])|(?<=(?:04|06|09|11)\.)(?:[0-2]\d|30)|(?<=02\.)(?:[0-1]\d|2[0-8])) (?:[0-1]\d|2[0-3])(?::[0-5]\d){2})");
    std::string text;
    std::cin.unsetf(std::ios::skipws);
    std::copy(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), std::back_inserter(text));
    for (auto it = std::sregex_iterator(text.begin(), text.end(), pattern); it != std::sregex_iterator(); ++it) {
        std::cout << it->str() << std::endl;
    }
    return 0;
}
