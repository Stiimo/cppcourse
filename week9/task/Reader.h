#pragma once

#include "ShmClient.h"
#include <thread>

class Reader : public ShmClient {
public:
    explicit Reader(const std::thread::id &uid);

    void run(const StopToken &stopToken) final;

private:
    std::thread::id m_uid;
    std::size_t m_last{0};
};

