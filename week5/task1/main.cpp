#include <iostream>
#include <iomanip>

int main() {
    std::cin.imbue(std::locale("en_US.UTF-8"));
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    long double money;
    std::cin >> std::get_money(money);
    money *= 10750;
    std::cout << std::showbase << std::put_money(money) << std::endl;
    return 0;
}
