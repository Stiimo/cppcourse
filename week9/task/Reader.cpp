#include <boost/interprocess/sync/sharable_lock.hpp>
#include "Reader.h"
#include "StopToken.h"
#include "Console.h"

using shared_lock = boost::interprocess::sharable_lock<shm::shared_mutex>;
using condition_lock = boost::interprocess::scoped_lock<shm::mutex>;

Reader::Reader(const std::thread::id &uid) : m_uid(uid) {
    shared_lock lock(*m_buffer_mutex);
    std::for_each(m_buffer->begin(), m_buffer->end(), [](const MsgData &data) {
        Console::instance()->putString(data);
    });
    if (!m_buffer->empty()) {
        const auto &data = m_buffer->back();
        m_last = std::hash<MsgData>{}(data);
    }
}

void Reader::run(const StopToken &stopToken) {
    auto console = Console::instance();
    while (!stopToken.stopRequested()) {
        {
            condition_lock lock(*m_condition_mutex);
            m_condition->wait(lock);
        }
        shared_lock lock(*m_buffer_mutex);
        if (m_buffer->empty()) {
            continue;
        }
        const auto &data = m_buffer->back();
        if (m_uid == data.uid) {
            continue;
        }
        auto hash = std::hash<MsgData>{}(data);
        if (hash != m_last) {
            console->putString(data);
            m_last = hash;
        }
    }
    console->putString("Reader is finishing work");
}