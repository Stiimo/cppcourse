#include "InterruptableThread.h"

StopToken InterruptableThread::stopToken() noexcept {
    return StopToken(m_stopState);
}

void InterruptableThread::start(const std::function<void(const StopToken &)> &target) {
    m_thread = ThreadPtr(new std::thread(target, stopToken()), [](std::thread *thread) {
        if (thread) {
            if (thread->joinable()) {
                thread->join();
            }
            delete thread;
        }
    });
}

void InterruptableThread::join() {
    m_thread->join();
}

bool InterruptableThread::joinable() const noexcept {
    return m_thread->joinable();
}
