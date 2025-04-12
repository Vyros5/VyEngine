#pragma once

#include <VyLib/vy_glfw.hpp>
#include "gui/vy_gui.hpp"
#include "io/input.hpp"
#include "io/camera.hpp"

#include "render/model.hpp"
#include "render/shader_program.hpp"

#include <stdlib.h>
#include <iostream>

namespace VyEngine::core
{
    struct WindowSettings
    {
        const char* title;
        int x, y, w, h;
        int wMin, hMin;
        int flags;
        float aspectRatio;
        glm::vec4 clearColor;

        WindowSettings();
    };
    
    class Window
    {
    private:

        // Window Object
        GLFWwindow* pWindow;

        ImGuiWindow mImGuiWindow;

        WindowSettings mWindowData;

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
        bool imguiEnabled = false;
        // Camera Object
        Camera* camera;

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
        Window();

        ~Window();

        void create(WindowSettings& winSettings);

        void init();

        void initCallbacks();

        
        void update();
        
        void processInput(double dt);
        
        void processWindowInput();
        
        void renderShader(ShaderProgram shader);
        
        void beginRender();
        void render();
        void endRender();

        void pollEvents();

        void newFrame();

        void shutdown();

        bool shouldClose();

        // Set if the window should close
        void setShouldClose(bool shouldClose);

        // Set window background color
        void setWindowColor(glm::vec4 v);

        WindowSettings getWindowSettings() { return core::WindowSettings(); }
    };
}