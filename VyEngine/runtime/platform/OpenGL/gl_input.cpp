#include "gl_input.hpp"

#include "platform/Windows/gl_window.hpp"
// #include <GLFW/glfw3.h>

namespace VyEngine
{

    bool Input::IsKeyPressed(KeyCode key)
    {
        return 0; // auto* window = static_cast<GLFWwindow*>
    }
    
    bool Input::IsKeyReleased(KeyCode key)
    {
        return 0;
    }
    
    
    bool Input::IsMousePressed(MouseCode button)
    {
        return 0;
    }
    
    // std::pair<float, float> Input::GetMousePosition()
    // {
    //     return {0, 0};
    // }
    
    float Input::GetMouseX()
    {
        return 0;
    }
    
    float Input::GetMouseY()
    {
        return 0;
    }
    
}