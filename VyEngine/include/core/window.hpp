#pragma once

#include <VyLib/vy_glfw.hpp>
#include "gui/vy_gui.hpp"
#include "io/input.hpp"
#include "io/camera.hpp"

#include "render/model.hpp"
#include "render/shader_program.hpp"

#include <stdlib.h>
#include <iostream>

class Window
{
    protected:

	// Window Object
	GLFWwindow* pWindow;

    // Window Values
    const char*  title;
    unsigned int scrWidth;
    unsigned int scrHeight;

    // GLFW Info
    int majVersion;
    int minVersion;

    // Background Color
    float bg[4];
    
    public:

    // Camera Object
    Camera* camera;

    VyGUI gui;
    
    // Camera Position
    glm::vec3 cameraPos;
    glm::vec3 cameraTarget;

    // Matrices
    glm::mat4 viewMatrix;
    glm::mat4 projMatrix;
    glm::mat4 modlMatrix;

    // Aspect Ratio
    float aspectRatio = 0;

    // Window Resize
    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
    
    // Window Constructor
    Window(int majVer, int minVer, unsigned int width, unsigned int height, const char* title);

    void initWindow();

    void initCallbacks();

    void initGUI();

    void update();

    void processInput(double dt);
    
    void processWindowInput();

    void renderShader(ShaderProgram shader);

    void renderGUI();

    void pollEvents();
    
    void newFrame();

    void cleanup();

    bool shouldClose();

    // Set if the window should close
    void setShouldClose(bool shouldClose);

    // Set window background color
    void setWindowColor(float r, float g, float b, float a);
};