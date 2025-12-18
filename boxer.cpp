#include <linux/joystick.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int main() {
    const char* device = "/dev/input/js0"; // may be js1, js2, etc.

    int fd = open(device, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open joystick");
        return 1;
    }

    js_event event;

    std::cout << "Listening to RadioMaster Boxer joystick...\n";
    std::cout << "Press Ctrl+C to stop.\n\n";

    while (true) {
        ssize_t bytes = read(fd, &event, sizeof(event));
        if (bytes != sizeof(event)) {
            perror("Read error");
            break;
        }

        // Ignore initialization events
        event.type &= ~JS_EVENT_INIT;

        if (event.type == JS_EVENT_AXIS) {
            std::cout
                << "Axis " << static_cast<int>(event.number)
                << " value: " << event.value
                << std::endl;
        }
        else if (event.type == JS_EVENT_BUTTON) {
            std::cout
                << "Button " << static_cast<int>(event.number)
                << (event.value ? " pressed" : " released")
                << std::endl;
        }
    }

    close(fd);
    return 0;
}

