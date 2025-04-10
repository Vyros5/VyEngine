#include "vy_glfw.hpp"

#include <iostream>

GLFWwindow* InitGLFW(int majorVer, int minorVer, int scrWidth, int scrHeight, const char* title)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        exit(0);
    }

    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    std::cout << "===<[GLFW " << major << "." << minor << "." << rev << " Initialized]>===\n";

    // GLFW Context ===============================================================================

	// Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);

	// Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Mazimize
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Window =====================================================================================

    // Initalize Window.
    GLFWwindow* glWindow = glfwCreateWindow(scrWidth, scrHeight, title, glfwGetPrimaryMonitor(), NULL);

	// Error handling.
	if (!glWindow)
	{
		const char* pDesc = NULL;
		int err = glfwGetError(&pDesc);
		std::cout << "Failed to create GLFW window: " << pDesc << "\n";
		exit(1);
	}

	// Set GLFW context.
	glfwMakeContextCurrent(glWindow);

    // GLAD =======================================================================================

    // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context\n";
		exit(0);
	}

    return glWindow;
}
