#include <atomic>
#include <memory>
#include <functional>
#include "StopToken.h"
#include <thread>

class InterruptableThread {
public:
    StopToken stopToken() noexcept;

    void start(const std::function<void(const StopToken &)> &target);

    [[nodiscard]] bool joinable() const noexcept;

    void join();

private:
    using ThreadPtr = std::unique_ptr<std::thread, std::function<void(std::thread *)>>;

    std::shared_ptr<std::atomic_bool> m_stopState{std::make_shared<std::atomic_bool>(false)};
    ThreadPtr m_thread;
};
