#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::string filetype(const fs::path &path) {
    if (is_directory(path)) {
        return "<dir>";
    } else if (is_symlink(path)) {
        return "<symlink>";
    } else {
        return "<file>";
    }
}

template<typename TP>
long to_timestamp(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                        + system_clock::now());
    return duration_cast<seconds>(sctp.time_since_epoch()).count();
}


long timestamp(const fs::path &path) {
    auto tp = fs::last_write_time(path);
    return to_timestamp(tp);
}

int main() {
    std::string requestedPath;
    std::getline(std::cin, requestedPath);
    if (requestedPath.empty()) {
        std::cout << "Input is empty" << std::endl;
        return 0;
    }
    fs::path path(requestedPath);
    if (!fs::exists(path)) {
        std::cerr << "Path does not exist" << std::endl;
    } else if (!is_directory(path)) {
        std::cout << path.filename() << ' ' << filetype(path) << ' ' << timestamp(path) << std::endl;
    } else {
        for (const auto &dirEntry: fs::directory_iterator{path}) {
            const auto &p = dirEntry.path();
            std::cout << p.filename() << ' ' << filetype(p) << ' ' << timestamp(p) << std::endl;
        }
    }
    return 0;
}
