#pragma once
#include <atomic>

struct StickState {
    std::atomic<float> lx{0.0f};
    std::atomic<float> ly{0.0f};
    std::atomic<float> rx{0.0f};
    std::atomic<float> ry{0.0f};
};
