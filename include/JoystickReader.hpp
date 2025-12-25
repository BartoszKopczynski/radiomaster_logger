#pragma once
#include <linux/joystick.h>
#include <string>
#include "RingBuffer.hpp"


enum class Stick : uint8_t {
    Left,
    Right
};

enum class AxisType : uint8_t {
    X,
    Y
};

struct StickEvent {
    uint32_t time_ms;
    Stick stick;
    AxisType axis;
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

