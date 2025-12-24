#pragma once
#include <fstream>
#include <atomic>
#include "JoystickReader.hpp"
#include "RingBuffer.hpp"

template <size_t BufferSize>
class BinaryLogger {
public:
    BinaryLogger(const std::string& path,
                 RingBuffer<StickEvent, BufferSize>& buffer,
                 std::atomic<bool>& running);

    void run();

private:
    std::ofstream file_;
    RingBuffer<StickEvent, BufferSize>& buffer_;
    std::atomic<bool>& running_;
};

