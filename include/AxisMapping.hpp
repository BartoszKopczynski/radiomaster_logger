#pragma once
#include <cstdint>
#include "JoystickReader.hpp"

inline bool mapAxis(uint8_t rawAxis,
                    Stick& stick,
                    AxisType& axis)
{
    switch (rawAxis) {
        case 0: stick = Stick::Right; axis = AxisType::X; return true; // Roll
        case 1: stick = Stick::Right; axis = AxisType::Y; return true; // Pitch
        case 2: stick = Stick::Left;  axis = AxisType::Y; return true; // Throttle
        case 3: stick = Stick::Left;  axis = AxisType::X; return true; // Yaw
        default:
            return false; // ignore knobs/switches
    }
}


