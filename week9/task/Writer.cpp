#include "Writer.h"
#include "StopToken.h"
#include "Console.h"
#include <boost/interprocess/sync/scoped_lock.hpp>

using unique_lock = boost::interprocess::scoped_lock<shm::shared_mutex>;
using condition_lock = boost::interprocess::scoped_lock<shm::mutex>;

void Writer::run(const StopToken &stopToken) {
    std::string msg;
    auto console = Console::instance();
    while (console->good()) {
        console->getString(msg);
        if (msg.empty()) { continue; }
        unique_lock lock(*m_buffer_mutex);
        auto alloc = shm::char_allocator(get_segment_manager());
        if (m_buffer->size() == 10) {
            m_buffer->pop_front();
        }
        m_buffer->emplace_back(std::this_thread::get_id(), msg, alloc);
        m_condition->notify_all();
    }
    stopToken.requestStop();
    m_condition->notify_all();
    console->putString("Writer is finishing work");
}
