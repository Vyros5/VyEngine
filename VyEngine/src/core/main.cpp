#include <window.hpp>

#include <iostream>


// Delta Time - Time between frames.
double dt = 0.0f; 

// Time of last frame.
double lastFrame = 0.0f; 

// GLFW Version
const unsigned int MAJ_VERSION = 3;
const unsigned int MIN_VERSION = 3;

// Window dimensions
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Title
const char* TITLE = "OpenGL Engine";


void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Main Window
    Window window(MAJ_VERSION, MIN_VERSION, SCR_WIDTH, SCR_HEIGHT, TITLE);


    while (!window.shouldClose())
    {
		// Delta Time (dt)
		double currentTime = glfwGetTime();
		dt = currentTime - lastFrame;
		lastFrame = currentTime;

		// Update Window
		window.update();

		// Process Input
		window.processInput(dt);

		// New Frame
		window.newFrame();
    }


    

    window.cleanup();
    return 0;
}