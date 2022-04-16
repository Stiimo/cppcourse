#include <boost/interprocess/sync/sharable_lock.hpp>
#include <iostream>
#include "Reader.h"
#include "StopToken.h"

using shared_lock = boost::interprocess::sharable_lock<shm::shared_mutex>;
using condition_lock = boost::interprocess::scoped_lock<shm::mutex>;

Reader::Reader(const std::thread::id &uid) : m_uid(uid) {
    shared_lock lock(*m_buffer_mutex);
    std::for_each(m_buffer->begin(), m_buffer->end(), [](const MsgData &data) {
        std::cout << data << std::endl;
    });
    if (!m_buffer->empty()) {
        const auto &data = m_buffer->back();
        m_last = std::hash<MsgData>{}(data);
    }
}

void Reader::run(const StopToken &stopToken) {
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
            std::cout << data << std::endl;
            m_last = hash;
        }
    }
    std::cout << "Reader is finishing work" << std::endl;
}