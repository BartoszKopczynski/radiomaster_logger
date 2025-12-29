#pragma once
#include "imgui.h"

inline void DrawStick2D(const char* label, float x, float y, float size = 200.0f) {
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImDrawList* draw = ImGui::GetWindowDrawList();

    ImVec2 center = { pos.x + size / 2, pos.y + size / 2 };
    float radius = size / 2;

    // Background
    draw->AddCircle(center, radius, IM_COL32(200,200,200,255), 64, 2.0f);
    draw->AddLine({center.x - radius, center.y}, {center.x + radius, center.y}, IM_COL32(100,100,100,255));
    draw->AddLine({center.x, center.y - radius}, {center.x, center.y + radius}, IM_COL32(100,100,100,255));

    // Stick position
    ImVec2 stick = {
        center.x + x * radius,
        center.y - y * radius
    };
    draw->AddCircleFilled(stick, 6.0f, IM_COL32(255,80,80,255));

    ImGui::Dummy({size, size});
    ImGui::Text("%s (%.2f, %.2f)", label, x, y);
}
