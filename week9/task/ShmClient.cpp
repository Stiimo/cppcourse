#include "ShmClient.h"

ShmClient::ShmClient()
        : m_shm(boost::interprocess::open_or_create, shared_memory_name, 65536) {
    m_ref_count = m_shm.find_or_construct<std::atomic_uint>("ref_count")(0);
    ++*m_ref_count;
    m_buffer = m_shm.find_or_construct<shm::list>("chat_buffer")(get_segment_manager());
    m_buffer_mutex = m_shm.find_or_construct<shm::shared_mutex>("buffer_mutex")();
    m_condition_mutex = m_shm.find_or_construct<shm::mutex>("condition_mutex")();
    m_condition = m_shm.find_or_construct<shm::condition>("condition")();
}

ShmClient::~ShmClient() {
    // TODO: check for dangling pointers
    if (!m_ref_count) {
        return;
    }
    --*m_ref_count;
    if (!*m_ref_count) {
        boost::interprocess::shared_memory_object::remove(shared_memory_name);
    }
}

ShmClient::ShmClient(ShmClient &&other) noexcept {
    if (this != &other) {
        m_shm = std::move(other.m_shm);
        m_ref_count = other.m_ref_count;
        m_buffer = other.m_buffer;
        m_buffer_mutex = other.m_buffer_mutex;
        m_condition_mutex = other.m_condition_mutex;
        m_condition = other.m_condition;
        other.m_ref_count = nullptr;
        other.m_buffer = nullptr;
        other.m_buffer_mutex = nullptr;
        other.m_condition_mutex = nullptr;
        other.m_condition = nullptr;
    }
}

ShmClient &ShmClient::operator=(ShmClient &&other) noexcept {
    if (this != &other) {
        m_shm = std::move(other.m_shm);
        m_ref_count = other.m_ref_count;
        m_buffer = other.m_buffer;
        m_buffer_mutex = other.m_buffer_mutex;
        m_condition_mutex = other.m_condition_mutex;
        m_condition = other.m_condition;
        other.m_ref_count = nullptr;
        other.m_buffer = nullptr;
        other.m_buffer_mutex = nullptr;
        other.m_condition_mutex = nullptr;
        other.m_condition = nullptr;
    }
    return *this;
}
