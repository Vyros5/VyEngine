#pragma once

struct GLFWwindow;

namespace VyEngine
{
    class OpenGLCallback
    {
        void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        void MouseWheelCallback(GLFWwindow* window, double dx, double dy);

        void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
        
        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
        void CharCallback(GLFWwindow* window, unsigned int keycode);
        
        void WinSizeCallback(GLFWwindow* window, int w, int h);
        void WinMinCallback(GLFWwindow* window);
        void WinMaxCallback(GLFWwindow* window);
        void WinCloseCallback(GLFWwindow* window);
    };
}