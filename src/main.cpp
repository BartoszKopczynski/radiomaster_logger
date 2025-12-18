#include <iostream>
#include <thread>
#include <chrono>

#include "RingBuffer.hpp"
#include "JoystickReader.hpp"
#include "CSVLogger.hpp"

constexpr size_t BUFFER_SIZE = 4096;

int main() {
    RingBuffer<StickEvent, BUFFER_SIZE> buffer;

    JoystickReader joystick("/dev/input/js0");
    CsvLogger logger("data/boxer_sticks.csv");

    std::cout << "Logging RadioMaster Boxer stick data...\n";

    while (true) {
        // Producer: read joystick
        StickEvent evt;
        if (joystick.readEvent(evt)) {
            buffer.push(evt); // if full, drop silently
        }

        // Consumer: write to file
        while (buffer.pop(evt)) {
            logger.log(evt);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

