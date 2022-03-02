#include <iostream>
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

struct PhoneBookEntry {
    std::string name;
    std::string phone;
};

using namespace boost::multi_index;

using PhoneBookEntryMultiIndex = multi_index_container<
        PhoneBookEntry, indexed_by<
                hashed_non_unique<
                        member<PhoneBookEntry, std::string, &PhoneBookEntry::name> >,
                random_access<>,
                ordered_non_unique<
                        member<PhoneBookEntry, std::string, &PhoneBookEntry::name> > > >;

constexpr int HashedInterface = 0;
constexpr int RandomAccessInterface = 1;
constexpr int OrderedInterface = 2;

int main() {
    PhoneBookEntryMultiIndex phones;
    phones.insert({"Anna", "456-14-45"});
    phones.insert({"Dmitry", "153-85-62"});
    phones.insert({"Egor", "123-56-66"});
    phones.insert({"Inna", "456-85-87"});
    phones.insert({"Denis", "632-58-61"});

    std::cout << "Hashed access" << std::endl;
    const auto &hashed = phones.get<HashedInterface>();
    auto it = hashed.find("Anna");
    std::cout << it->phone << std::endl;
    std::cout << std::endl;

    std::cout << "Random access" << std::endl;
    const auto &random = phones.get<RandomAccessInterface>();
    for (const auto &v: random) {
        std::cout << v.name << ' ' << v.phone << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Ordered access" << std::endl;
    const auto &ordered = phones.get<OrderedInterface>();
    auto begin = ordered.lower_bound("D");
    auto end = ordered.lower_bound("E");
    for (; begin != end; ++begin) {
        std::cout << begin->name << ' ' << begin->phone << std::endl;
    }
    return 0;
}
