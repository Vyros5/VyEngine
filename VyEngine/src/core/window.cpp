#include "core/window.hpp"

Window::Window(int majVer, int minVer, unsigned int width, unsigned int height, const char* title) :
    majVersion(majVer), minVersion(minVer), scrWidth(width), scrHeight(height), title(title)
{
    // Set Window
    pWindow = InitGLFW(majVer, minVer, width, height, title);

    // Initialize
    if (pWindow)
    {
        initWindow();
    }
    
	// Aspect Ratio
	aspectRatio = (float)scrWidth / (float)scrHeight;

	// Window color
	setWindowColor(0.15f, 0.15f, 0.15f, 1.0f);
}


void Window::initWindow()
{
	// Setup screen viewport.
	glViewport(0, 0, scrWidth, scrHeight);

	// Enable Depth Testing.
	glEnable(GL_DEPTH_TEST);

	// Disable cursor on startup.
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Window::initCallbacks()
{

}


void Window::update()
{
	// Set Background Color
	glClearColor(bg[0], bg[1], bg[2], bg[3]);

	// Clear Occupied Bits
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Window::newFrame()
{
	// Swap Buffers and Handle Events.
	glfwSwapBuffers(pWindow);
	glfwPollEvents();
}


void Window::processInput(double dt)
{
	processWindowInput();
}


void Window::processWindowInput()
{
    if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		setShouldClose(true);
}


void Window::cleanup()
{
    glfwTerminate();
}


bool Window::shouldClose()
{
    return glfwWindowShouldClose(pWindow);
}


// Set if the window should close
void Window::setShouldClose(bool shouldClose)
{
    glfwSetWindowShouldClose(pWindow, shouldClose);
}


// Set window background color
void Window::setWindowColor(float r, float g, float b, float a)
{
	// Set RGBA of the background color.
	bg[0] = r;
	bg[1] = g;
	bg[2] = b;
	bg[3] = a;
}