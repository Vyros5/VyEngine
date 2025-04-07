#pragma once

#include <vy_glfw.hpp>

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

    // Aspect Ratio
    float aspectRatio = 0;
    
    
    // Window Constructor
    Window(int majVer, int minVer, unsigned int width, unsigned int height, const char* title);

    void initWindow();

    void initCallbacks();

    void update();

    void newFrame();

    void processInput(double dt);

    void processWindowInput();

    void cleanup();

    bool shouldClose();

    // Set if the window should close
    void setShouldClose(bool shouldClose);

    // Set window background color
    void setWindowColor(float r, float g, float b, float a);
};