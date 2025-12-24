#include "BinaryLogger.hpp"
#include <thread>
#include <chrono>
#include <iostream> 

template <size_t BufferSize>
BinaryLogger<BufferSize>::BinaryLogger(
    const std::string& path,
    RingBuffer<StickEvent, BufferSize>& buffer,
    std::atomic<bool>& running)
    : buffer_(buffer), running_(running)
{
    file_.open(path, std::ios::binary);
}

template <size_t BufferSize>
void BinaryLogger<BufferSize>::run() {
    std::cout << " starting thread" << std::endl;
    StickEvent evt;
    while (running_) {
    // std::cout << " running thread" << std::endl;                 // endless loop
        while (buffer_.pop(evt)) {  // stick moved
    std::cout << " pop" << std::endl;
            std::cout << evt.time_ms << std::endl;
            std::cout << evt.axis << std::endl;
            std::cout << evt.value << std::endl;
            file_.write(reinterpret_cast<const char*>(&evt),
                        sizeof(StickEvent));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // flush remaining data
    while (buffer_.pop(evt)) {
        file_.write(reinterpret_cast<const char*>(&evt),
                    sizeof(StickEvent));
    }
}

// Explicit instantiation
template class BinaryLogger<40>;


