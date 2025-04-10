#include "window.hpp"

#pragma region Callbacks

// Window Resize
void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

#pragma endregion




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

	// Initialize Callbacks
	initCallbacks();
	
	std::cout << "WINDOW::initWindow: Initialized window.\n";
}


void Window::initCallbacks()
{
	// GLFW Error Callback
	GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun cbfun);

	// Frame Resize Callback
	glfwSetFramebufferSizeCallback(pWindow, frameBufferSizeCallback);

	// Keyboard Key Callback
	glfwSetKeyCallback(pWindow, Keyboard::keyCallback);

	// Mouse Cursor Callback
	glfwSetCursorPosCallback(pWindow, Mouse::cursorPosCallback);

	// Mouse Button Callback
	glfwSetMouseButtonCallback(pWindow, Mouse::mouseButtonCallback);

	// Mouse Scroll Callback
	glfwSetScrollCallback(pWindow, Mouse::mouseWheelCallback);
}


void Window::update()
{
	// Set Background Color
	glClearColor(bg[0], bg[1], bg[2], bg[3]);

	// Clear Occupied Bits
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Window::renderShader(ShaderProgram shader)
{
	shader.setUniform("view", viewMatrix);
	shader.setUniform("proj", projMatrix);
}


void Window::newFrame()
{
	// Swap Buffers and Handle Events.
	glfwSwapBuffers(pWindow);
	glfwPollEvents();
}


void Window::processInput(double dt)
{
	// Window Inputs
	processWindowInput();

	
	// Camera Direction Control
	double dx = Mouse::getDX();
	double dy = Mouse::getDY();

	if (dx != 0 || dy != 0)
	{
		camera->updateDirection(dx, dy);
	}


	// Camera Zoom Control
	double scrollDy = Mouse::getScrollDY();

	if (scrollDy != 0)
	{
		camera->updateZoom(scrollDy);
	}


	// Camera Position Control
	if (Keyboard::key(GLFW_KEY_W))
	{
		camera->updatePosition(CameraDirection::FORWARD, dt);	// -Z
	}

	if (Keyboard::key(GLFW_KEY_S))
	{
		camera->updatePosition(CameraDirection::BACKWARD, dt);	// +Z
	}

	if (Keyboard::key(GLFW_KEY_D))
	{
		camera->updatePosition(CameraDirection::RIGHT, dt);		// +X
	}

	if (Keyboard::key(GLFW_KEY_A))
	{
		camera->updatePosition(CameraDirection::LEFT, dt);		// -X
	}

	if (Keyboard::key(GLFW_KEY_SPACE))
	{
		camera->updatePosition(CameraDirection::UP, dt);		// +Y
	}

	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT))
	{
		camera->updatePosition(CameraDirection::DOWN, dt);		// -Y
	}


	// Set Matrices
	viewMatrix = camera->getViewMatrix();
	projMatrix = camera->getProjMatrix();

	// Set Camera Position
	cameraPos 	 = camera->getPosition();
	cameraTarget = camera->getTarget();
}


void Window::processWindowInput()
{
	// Exit Window
	if (Keyboard::key(GLFW_KEY_ESCAPE))
	{
		std::cout << "EXIT\n";
		setShouldClose(true);
	}	
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