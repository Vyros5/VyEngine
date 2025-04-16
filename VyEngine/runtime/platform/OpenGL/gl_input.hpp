#pragma once

#include "input/input_codes.hpp"

namespace VyEngine
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsKeyReleased(KeyCode key);

        static bool IsMousePressed(MouseCode button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}