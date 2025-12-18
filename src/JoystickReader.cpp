#include "JoystickReader.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>

JoystickReader::JoystickReader(const std::string& device) {
    fd_ = open(device.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd_ < 0) {
        throw std::runtime_error("Failed to open joystick");
    }
}

JoystickReader::~JoystickReader() {
    if (fd_ >= 0)
        close(fd_);
}

bool JoystickReader::readEvent(StickEvent& evt) {
    js_event js;
    ssize_t bytes = read(fd_, &js, sizeof(js));
    if (bytes != sizeof(js))
        return false;

    js.type &= ~JS_EVENT_INIT;
    if (js.type != JS_EVENT_AXIS)
        return false;

    evt.time_ms = js.time;
    evt.axis = js.number;
    evt.value = js.value;
    return true;
}
