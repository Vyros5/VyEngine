#include "entry_point.hpp"

#include "VyLib/vy_file.hpp"
#include "VyLib/vy_logger.hpp"

// ================================================================================================

int main(int argc, char** argv)
{
	srand(static_cast<uint32_t>(time(0)));

	VyEngine::Log::Init();

	auto app = VyEngine::CreateApplication();
	app->Run();
	delete app;

	return 0;
}


	// // Main Window
	// VyEngine::core::Window window;

	// WindowSettings winData = window.getWindowSettings();

	// window.create(winData);

	// // Main Camera
	// CameraSettings camSettings;

	// window.camera = new Camera(camSettings);


	// Model Paths 
	// const std::string modelPath = "C:/dev/cpp/VyEngine/VyEngine/assets/models/backpack/backpack.obj";


	// // Models
	// Model objectModel(modelPath);

	// // Shaders
	// ShaderProgram modelShader;
	// modelShader.init(
	// 	"C:/dev/cpp/VyEngine/VyEngine/assets/shaders/model.vert", 
	// 	"C:/dev/cpp/VyEngine/VyEngine/assets/shaders/model.frag"
	// );




	// MAIN LOOP ==================================================================================

	// while (!window.shouldClose())
	// {
	// 	// Delta Time (dt)
	// 	double currentTime = glfwGetTime();
	// 	dt = currentTime - lastFrame;
	// 	lastFrame = currentTime;

	// 	window.pollEvents();
		
	// 	// Process Input
	// 	window.processInput(dt);

	// 	window.render();

	// 	// Model Shader
	// 	modelShader.activate();
	// 	window.renderShader(modelShader);

	// 	glm::mat4 model = glm::mat4(1.0f);
	// 	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
	// 	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	// 	modelShader.setUniform("model", model);

	// 	// Render Model
	// 	objectModel.render(modelShader);

	// 	window.endRender();
	// }

	// ============================================================================================
	
	// Cleanup Objects
	// objectModel.cleanup();
	// modelShader.destroy();
	
