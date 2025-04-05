#include "vy_glfw.hpp"

#include <stdlib.h>
#include <iostream>

// Initialize GLFW
static void glfwLibInit()
{
	if (!glfwInit())
	{
        std::cout << "ERROR: Failed to initialize GLFW\n";
		glfwTerminate();
	}

	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
    std::cout << "GLFW " << major << "." << minor << "." << rev << " Initialized\n";
}


// Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
static void gladLibInit()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: Failed to initialize OpenGL Context\n";
		glfwTerminate();
	}
}


GLFWwindow* glWindow(int majVer, int minVer, int scrW, int scrH, const char* title)
{
    // Initialize GLFW
    glfwLibInit();

    // GLFW Context ----------------------------------------------------

    // Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majVer);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minVer);

    // Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // WINDOW ----------------------------------------------------------

    // Initalize Window.
    GLFWwindow* pWindow = glfwCreateWindow(scrW, scrH, title, NULL, NULL);

    // Error handling.
    if (!pWindow)
    {
        const char* pDesc = NULL;
        int err = glfwGetError(&pDesc);
        std::cout << "ERROR: Failed to create GLFW Window: " << pDesc << "\n";
        glfwTerminate();
    }

    // Set GLFW context.
    glfwMakeContextCurrent(pWindow);

	// Initialize GLAD
	gladLibInit();

    return pWindow;
}