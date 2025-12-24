#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#include "RingBuffer.hpp"
#include "JoystickReader.hpp"
#include "BinaryLogger.hpp"

constexpr size_t BUFFER_SIZE = 40;

int main() {
    RingBuffer<StickEvent, BUFFER_SIZE> buffer;
    std::atomic<bool> running{true};

    JoystickReader joystick("/dev/input/js0");
    BinaryLogger<BUFFER_SIZE> logger(
        "data/boxer_sticks.bin", buffer, running);

    std::thread loggerThread(&BinaryLogger<BUFFER_SIZE>::run, &logger);

    std::cout << "Logging stick data (Ctrl+C to stop)...\n";

    while (running) {
        StickEvent evt;
        if (joystick.readEvent(evt)) {
            std::cout << " evt::: " << evt.value << std::endl;
            buffer.push(evt); // drop if full
        }
        std::this_thread::sleep_for(std::chrono::microseconds(200));
    }

    loggerThread.join();
    return 0;
}

