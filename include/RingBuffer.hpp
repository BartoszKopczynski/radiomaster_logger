#pragma once
#include <array>
#include <atomic>

template <typename T, size_t Size>
class RingBuffer {
public:
    RingBuffer() : head_(0), tail_(0) {}

    bool push(const T& item) {
        size_t next = (head_ + 1) % Size;
        if (next == tail_) {
            return false; // buffer full
        }
        buffer_[head_] = item;
        head_ = next;
        return true;
    }

    bool pop(T& item) {
        if (tail_ == head_) {
            return false; // empty
        }
        item = buffer_[tail_];
        tail_ = (tail_ + 1) % Size;
        return true;
    }

private:
    std::array<T, Size> buffer_;
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;
};


