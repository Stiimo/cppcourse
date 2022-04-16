#pragma once

#include <ostream>
#include <thread>
#include <chrono>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/functional/hash.hpp>

namespace shm {
    using SegmentManager = boost::interprocess::managed_shared_memory::segment_manager;
    using char_allocator = boost::interprocess::allocator<char,
            SegmentManager>;
    using string = boost::interprocess::basic_string<char,
            std::char_traits<char>, char_allocator>;
}

// Otherwise, boost does not support hash for std::thread::id
class UID {
public:
    // no explicit because I want it this way
    UID(const std::thread::id &id) : m_id(id) {}

private:
    friend std::size_t hash_value(const UID &uid) {
        return std::hash<std::thread::id>{}(uid.m_id);
    }

    friend std::ostream &operator<<(std::ostream &out, const UID &uid) {
        out << uid.m_id;
        return out;
    }

    friend bool operator==(const UID &lhs, const UID &rhs) {
        return lhs.m_id == rhs.m_id;
    }

    std::thread::id m_id;
};

struct MsgData {
    UID uid;
    long ts;
    shm::string msg;

    MsgData(std::thread::id uid, const std::string &msg, const shm::char_allocator &alloc) :
            uid(uid),
            ts(std::chrono::duration_cast<std::chrono::seconds>(clock::now().time_since_epoch()).count()),
            msg(msg.c_str(), alloc) {}

private:
    using clock = std::chrono::system_clock;
};

namespace shm {
    using MsgDataAllocator = boost::interprocess::allocator<MsgData, SegmentManager>;
}

template<>
struct std::hash<MsgData> {
    std::size_t operator()(const MsgData &data) const noexcept {
        std::size_t seed = 0;
        boost::hash_combine(seed, data.uid);
        boost::hash_combine(seed, data.ts);
        boost::hash_combine(seed, data.msg);
        return seed;
    }
};

inline std::ostream &operator<<(std::ostream &out, const MsgData &data) {
    // TODO: ts to normal view
    out << "[ u:" << data.uid << " at " << data.ts << " ] " << data.msg;
    return out;
}