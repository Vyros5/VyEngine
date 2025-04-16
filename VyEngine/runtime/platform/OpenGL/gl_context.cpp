#include "gl_context.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

#include "vy_logger.hpp"

namespace VyEngine
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : mWindowHandle(windowHandle) {}

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(mWindowHandle);

        // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize OpenGL context\n";
			exit(0);
		}

        VY_CORE_INFO("[OpenGL Info]");
        VY_CORE_INFO("- Vendor:   {0}", (const char*)glGetString(GL_VENDOR));
        VY_CORE_INFO("- Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        VY_CORE_INFO("- Version:  {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(mWindowHandle);
    }
}