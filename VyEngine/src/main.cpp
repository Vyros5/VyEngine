#include "window.hpp"

#include <iostream>


// Delta Time - Time between frames.
double dt = 0.0f; 

// Time of last frame.
double lastFrame = 0.0f; 

// GLFW Version
const unsigned int MAJ_VERSION = 4;
const unsigned int MIN_VERSION = 5;

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
	CameraSettings camSettings;
	camSettings.aspectRatio = aspectRatio;

	window.camera = new Camera(camSettings);


	// Model Paths 
	const std::string modelPath = "C:/dev/cpp/VyEngine/VyEngine/assets/models/backpack/backpack.obj";


	// Models
	Model objectModel(modelPath);

	// Shaders
	ShaderProgram modelShader;
	modelShader.init("C:/dev/cpp/VyEngine/VyEngine/assets/shaders/model.vert", "C:/dev/cpp/VyEngine/VyEngine/assets/shaders/model.frag");

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

		// Model Shader
		modelShader.activate();
		window.renderShader(modelShader);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		modelShader.setUniform("model", model);

		// Render Model
		objectModel.render(modelShader);


		// Swap Frames
		window.newFrame();
    }

	// ============================================================================================
    
	// Cleanup Objects

    window.cleanup();
    return 0;
}