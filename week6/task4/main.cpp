#include <iostream>
#include <iterator>
#include <vector>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

class Person {
public:
    Person() = default;

    [[nodiscard]] nlohmann::json toJson() const {
        return nlohmann::json{{"name",    m_name},
                              {"surname", m_surname},
                              {"age",     m_age}};
    }

    friend std::istream &operator>>(std::istream &s, Person &p) {
        return s >> p.m_name >> p.m_surname >> p.m_age;
    }

private:
    std::string m_name;
    std::string m_surname;
    size_t m_age{0};
};

int main() {
    std::vector<Person> people;
    std::copy(std::istream_iterator<Person>(std::cin), std::istream_iterator<Person>(), std::back_inserter(people));

    fs::path outPath("json_files");
    fs::create_directory(outPath);
    for (size_t i = 0; i < people.size(); ++i) {
        std::ofstream fout(outPath / ("object_" + std::to_string(i) + ".json"));
        fout << std::setw(4) << people[i].toJson() << std::endl;
    }
    return 0;
}
