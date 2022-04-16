#pragma once

#include "types.h"
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/containers/list.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>

#include <atomic>
#include <string>

namespace shm {
    using memory = boost::interprocess::managed_shared_memory;
    using mutex = boost::interprocess::interprocess_mutex;
    using shared_mutex = boost::interprocess::interprocess_sharable_mutex;
    using condition = boost::interprocess::interprocess_condition;
    using list = boost::interprocess::list<MsgData, MsgDataAllocator>;
}

class StopToken;

class ShmClient {
public:
    explicit ShmClient();

    virtual ~ShmClient();

    // No copy
    ShmClient(const ShmClient &other) = delete;

    ShmClient &operator=(const ShmClient &other) = delete;

    // Only move :)
    ShmClient(ShmClient &&other) noexcept;

    ShmClient &operator=(ShmClient &&other) noexcept;

    virtual void run(const StopToken &stopToken) = 0;

protected:
    /// @note For internal use only! Passing this pointer
    /// outside may result in dangling pointer situation!
    auto get_segment_manager() noexcept { return m_shm.get_segment_manager(); }

    shm::list *m_buffer;
    shm::shared_mutex *m_buffer_mutex;
    shm::mutex *m_condition_mutex;
    shm::condition *m_condition;

private:
    shm::memory m_shm;
    std::atomic_uint *m_ref_count;

    constexpr static const char *shared_memory_name{"managed_shared_memory"};
};
