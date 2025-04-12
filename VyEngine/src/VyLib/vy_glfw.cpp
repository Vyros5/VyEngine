#include "VyLib/vy_glfw.hpp"

#include <iostream>

namespace VyEngine::core
{
	GLFWwindow* InitGLFW(int scrWidth, int scrHeight, const char* title)
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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

		// Profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Mazimize
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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

		// glEnable(GL_DEBUG_OUTPUT);
		// glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		// glDebugMessageCallback(core::glDebugOutput, nullptr);
		// glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);

		return glWindow;
	}


	void glDebugOutput(
		GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char *message,
		const void *userParam)
	{
		GLuint ignore_ids[1] = { 131185 }; // "will use video memory..."

		for (int i = 0 ; i < sizeof(ignore_ids) / sizeof(ignore_ids[0]) ; i++) 
		{
			if (id == ignore_ids[i]) 
			{
				return;
			}
		}

		printf("!!! [Debug callback] !!!\n");
		printf("Debug message: (ID %d), %s\n", id, message);

		printf("- Message source: ");
		switch (source)
		{
			case GL_DEBUG_SOURCE_API:             printf("API\n"); break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   printf("Window System\n"); break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: printf("Shader Compiler\n"); break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:     printf("Third Party\n"); break;
			case GL_DEBUG_SOURCE_APPLICATION:     printf("Application\n"); break;
			case GL_DEBUG_SOURCE_OTHER:           printf("Other\n"); break;
		}

		printf("- Error type: ");
		switch (type)
		{
			case GL_DEBUG_TYPE_ERROR:               printf("Error\n"); break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: printf("Deprecated Behaviour\n"); break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  printf("Undefined Behaviour\n"); break;
			case GL_DEBUG_TYPE_PORTABILITY:         printf("Portability\n"); break;
			case GL_DEBUG_TYPE_PERFORMANCE:         printf("Performance\n"); break;
			case GL_DEBUG_TYPE_MARKER:              printf("Marker\n"); break;
			case GL_DEBUG_TYPE_PUSH_GROUP:          printf("Push Group\n"); break;
			case GL_DEBUG_TYPE_POP_GROUP:           printf("Pop Group\n"); break;
			case GL_DEBUG_TYPE_OTHER:               printf("Other\n"); break;
		}

		printf("- Severity: ");
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         printf("High\n"); break;
			case GL_DEBUG_SEVERITY_MEDIUM:       printf("Medium\n"); break;
			case GL_DEBUG_SEVERITY_LOW:          printf("Low\n"); break;
			case GL_DEBUG_SEVERITY_NOTIFICATION: printf("Notification\n"); break;
		}
		printf("\n");
	}
}