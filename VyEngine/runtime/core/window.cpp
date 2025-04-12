#include "window.hpp"

#pragma region Callbacks

namespace VyEngine::core
{

	// Window Resize
	void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	
	#pragma endregion
	
	WindowSettings::WindowSettings()
	{
		title = "VyEngine";
		x = 0;
		y = 0;
		w = 1920;
		h = 1080;
		wMin = 320;
		hMin = 180;
		flags = 0;
		aspectRatio = 16.0f / 9.0f;
		clearColor = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
	}
	
	
	
	Window::Window() : pWindow(nullptr) {}

	Window::~Window()
	{
		if (pWindow) { shutdown(); }
	}
	

	void Window::create(WindowSettings& data)
	{
		mWindowData = data;
		
		// Set Window
		pWindow = InitGLFW(data.w, data.h, data.title);
	
		// Initialize
		if (pWindow)
		{
			init();
		}
		
		// Aspect Ratio
		aspectRatio = data.aspectRatio;
		
		// Window color
		setWindowColor(data.clearColor);
	}


	void Window::init()
	{
		// Setup screen viewport.
		glViewport(0, 0, mWindowData.w, mWindowData.h);

		// Enable Depth Testing.
		glEnable(GL_DEPTH_TEST);

		// Disable cursor on startup.
		// glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Initialize Callbacks
		initCallbacks();

		// Initialize ImGui Window
		mImGuiWindow.init(pWindow);
		
		std::cout << "WINDOW::initWindow: Initialized window.\n\n";
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
		// glClearColor(bg[0], bg[1], bg[2], bg[3]);

	}
	
	void Window::beginRender()
	{
		
		// Clear Occupied Bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void Window::renderShader(ShaderProgram shader)
	{
		shader.setUniform("view", viewMatrix);
		shader.setUniform("proj", projMatrix);
	}


	void Window::render()
	{
		
		int display_w, display_h;
		glfwGetFramebufferSize(pWindow, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		
		// Set Background Color
		glClearColor(bg[0], bg[1], bg[2], bg[3]);
		
		// Clear Occupied Bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	}
	
	void Window::endRender()
	{
		if (imguiEnabled)
		{
			mImGuiWindow.beginRender();
			
			// Render GUI elements.
			ImGui::ShowDemoWindow();
			
			mImGuiWindow.endRender();
		}

		// Swap Frames
		newFrame();
	}


	void Window::pollEvents()
	{
		// Handle Events
		glfwPollEvents();

		if (glfwGetWindowAttrib(pWindow, GLFW_ICONIFIED) != 0)
		{
			ImGui_ImplGlfw_Sleep(10);
		}
	}

	void Window::newFrame()
	{
		// Swap Buffers
		glfwSwapBuffers(pWindow);
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
			camera->updatePosition(CameraDirection::FORWARD, dt);  // -Z
		}

		if (Keyboard::key(GLFW_KEY_S))
		{
			camera->updatePosition(CameraDirection::BACKWARD, dt);  // +Z
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
			setShouldClose(true);
		}

		if (Keyboard::key(GLFW_KEY_TAB))
		{
			imguiEnabled = !imguiEnabled;
		}	
	}


	void Window::shutdown()
	{
		mImGuiWindow.shutdown();
		glfwDestroyWindow(pWindow);
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
	void Window::setWindowColor(glm::vec4 v)
	{
		// Set RGBA of the background color.
		bg[0] = v.r;
		bg[1] = v.g;
		bg[2] = v.b;
		bg[3] = v.a;
	}
}