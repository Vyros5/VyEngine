#include "window.hpp"

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
const char* TITLE = "VyEngine";

// ================================================================================================

int main()
{
    // Main Window
    Window window(MAJ_VERSION, MIN_VERSION, SCR_WIDTH, SCR_HEIGHT, TITLE);

	float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;

	// Main Camera
	window.camera = new Camera(aspectRatio, glm::vec3(0.0f));



	// MAIN LOOP ==================================================================================

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

		// Swap Frames
		window.newFrame();
    }

	// ============================================================================================
    
	// Cleanup Objects

    window.cleanup();
    return 0;
}