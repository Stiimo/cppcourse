#include "StopToken.h"

StopToken::StopToken(const std::shared_ptr<std::atomic_bool> &stopState) noexcept: m_stopState(stopState) {
}

void StopToken::requestStop() const noexcept {
    auto stopState = m_stopState.lock();
    if (!stopState) {
        return;
    }
    *stopState = true;
}

bool StopToken::stopRequested() const noexcept {
    auto stopState = m_stopState.lock();
    if (!stopState) {
        return false;
    }
    return *stopState;
}
