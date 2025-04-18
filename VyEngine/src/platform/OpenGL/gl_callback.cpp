#include "gl_callback.hpp"
#include <GLFW/glfw3.h>
#include "event/event_manager.hpp"

namespace VyEngine
{
    void OpenGLCallback::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        auto handler = static_cast<GLFWwindow*>(glfwGetWindowUserPointer(window));
        
    }

    void OpenGLCallback::MouseWheelCallback(GLFWwindow* window, double dx, double dy)
    {

    }


    void OpenGLCallback::CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
    {

    }

    
    void OpenGLCallback::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {

    }

    void OpenGLCallback::CharCallback(GLFWwindow* window, unsigned int keycode)
    {

    }

    
    void OpenGLCallback::WinSizeCallback(GLFWwindow* window, int w, int h)
    {

    }

    void OpenGLCallback::WinMinCallback(GLFWwindow* window)
    {

    }

    void OpenGLCallback::WinMaxCallback(GLFWwindow* window)
    {

    }

    void OpenGLCallback::WinCloseCallback(GLFWwindow* window)
    {

    }
}