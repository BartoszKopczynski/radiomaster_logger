#pragma once
#include <linux/joystick.h>
#include <string>
#include "RingBuffer.hpp"

struct StickEvent {
    uint32_t time_ms;
    uint8_t axis;
    int16_t value;
};

class JoystickReader {
public:
    JoystickReader(const std::string& device);
    ~JoystickReader();

    bool readEvent(StickEvent& evt);

private:
    int fd_;
};

