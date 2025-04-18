#include "gl_input.hpp"

#include "core/application.hpp"
#include <GLFW/glfw3.h>
#include "platform/Windows/gl_window.hpp"

namespace VyEngine
{
    bool Input::IsKeyPressed(KeyCode key)
    {
        auto* window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow()->GetNativeWindow());
        auto state = glfwGetKey(window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    
    bool Input::IsKeyReleased(KeyCode key)
    {
        auto* window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow()->GetNativeWindow());
        auto state = glfwGetKey(window, key);
        return state == GLFW_RELEASE;
    }
    
    
    bool Input::IsMousePressed(MouseCode button)
    {
        auto* window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow()->GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    
    std::pair<float, float> Input::GetMousePosition()
    {
        auto* window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow()->GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return std::make_pair((float)xPos, (float)yPos);
    }
    
    float Input::GetMouseX()
    {
        return GetMousePosition().first;
    }
    
    float Input::GetMouseY()
    {
        return GetMousePosition().second;
    }
    
}