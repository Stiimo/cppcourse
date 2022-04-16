#pragma once

#include <memory>
#include <atomic>

class StopToken {
public:
    void requestStop() const noexcept;

    [[nodiscard]] bool stopRequested() const noexcept;

private:
    friend class InterruptableThread;

    explicit StopToken(const std::shared_ptr<std::atomic_bool> &stopState) noexcept;

    std::weak_ptr<std::atomic_bool> m_stopState;
};
