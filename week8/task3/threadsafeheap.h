#pragma once

#include <vector>
#include <shared_mutex>

template<typename T, typename Compare = std::greater<T>>
class ThreadSafeHeap {
public:
    explicit ThreadSafeHeap(Compare cmp = Compare()) : mCmp(cmp) {}

    explicit ThreadSafeHeap(const std::vector<T> &v, Compare cmp = Compare())
            : mHeap(v), mCmp(cmp) {
        std::make_heap(std::begin(mHeap), std::end(mHeap), mCmp);
    }

    [[nodiscard]] T top() const {
        std::shared_lock lock(mMutex);
        if (mHeap.empty()) {
            throw std::range_error("heap is empty");
        }
        return mHeap[0];
    }

    void pop(T &ref) {
        std::unique_lock lock(mMutex);
        if (mHeap.empty()) {
            throw std::range_error("heap is empty");
        }
        ref = mHeap[0];
        std::pop_heap(std::begin(mHeap), std::end(mHeap), mCmp);
    }

    void push(T value) {
        std::unique_lock lock(mMutex);
        mHeap.push_back(value);
        std::push_heap(std::begin(mHeap), std::end(mHeap), mCmp);
    }

private:
    std::vector<T> mHeap;
    Compare mCmp;
    std::shared_mutex mMutex;
};
