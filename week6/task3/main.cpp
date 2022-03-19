#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

std::string file_type(const fs::path &path) {
    auto status = fs::status(path);
    switch (status.type()) {
        case fs::file_type::none:
            return "<none>";
        case fs::file_type::not_found:
            return "<not found>";
        case fs::file_type::regular:
            return "<file>";
        case fs::file_type::directory:
            return "<dir>";
        case fs::file_type::symlink:
            return "<symlink>";
        case fs::file_type::block:
            return "<block>";
        case fs::file_type::character:
            return "<character>";
        case fs::file_type::fifo:
            return "<fifo>";
        case fs::file_type::socket:
            return "<socket>";
        case fs::file_type::unknown:
            return "<unknown>";
    }
}

template<typename TP>
long to_timestamp(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
    return duration_cast<seconds>(sctp.time_since_epoch()).count();
}

std::string timestamp(const fs::path &path) {
    auto tp = fs::last_write_time(path);
    return std::to_string(to_timestamp(tp));
}

uintmax_t file_size(const fs::path &path) {
    if (fs::is_directory(path)) {
        uintmax_t totalSize = 0;
        for (const auto &dirEntry: fs::directory_iterator{path}) {
            totalSize += ::file_size(dirEntry.path());
        }
        return totalSize;
    } else {
        return fs::file_size(path);
    }
}

class Walker {
public:
    explicit Walker(const fs::path &path) {
        if (!fs::exists(path)) {
            std::cerr << "Path does not exist" << std::endl;
            return;
        } else if (!fs::is_directory(path)) {
            m_entries.push_back({path.filename(), file_type(path), std::to_string(::file_size(path)), timestamp(path)});
        } else {
            for (const auto &dirEntry: fs::directory_iterator{path}) {
                const auto &p = dirEntry.path();
                m_entries.push_back({p.filename(), file_type(p), std::to_string(::file_size(p)), timestamp(p)});
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Walker &walker) {
        if (walker.m_entries.empty()) {
            return os;
        }
        size_t filenameWidth = 4;
        size_t filetypeWidth = 4;
        size_t sizeWidth = 12;
        size_t timestampWidth = 9;
        for (const auto &entry: walker.m_entries) {
            filenameWidth = std::max(filenameWidth, entry.filename.size());
            filetypeWidth = std::max(filetypeWidth, entry.filetype.size());
            sizeWidth = std::max(sizeWidth, entry.size.size());
            timestampWidth = std::max(timestampWidth, entry.timestamp.size());
        }
        std::cout << std::internal << std::setw(filenameWidth) << "name" << '|' << std::setw(filetypeWidth) << "type"
                  << '|' << std::setw(sizeWidth) << "size [bytes]" << '|' << std::setw(timestampWidth) << "timestamp"
                  << std::endl;
        std::cout << std::setfill('-') << std::setw(filenameWidth + filetypeWidth + sizeWidth + timestampWidth + 3)
                  << '-' << std::endl;
        for (const auto &entry: walker.m_entries) {
            std::cout << std::setfill(' ') << std::right << std::setw(filenameWidth) << entry.filename << '|'
                      << std::setw(filetypeWidth) << entry.filetype << '|' << std::setw(sizeWidth) << entry.size << '|'
                      << std::setw(timestampWidth) << entry.timestamp << std::endl;
        }
        return os;
    }

private:
    struct Entry {
        std::string filename;
        std::string filetype;
        std::string size;
        std::string timestamp;
    };

    std::vector<Entry> m_entries;
};


int main() {
    std::string requestedPath;
    std::getline(std::cin, requestedPath);
    if (requestedPath.empty()) {
        std::cout << "Input is empty" << std::endl;
        return 0;
    }
    Walker walker(requestedPath);
    std::cout << walker;
    return 0;
}
