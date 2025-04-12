#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glfw/glfw3.h>


namespace VyEngine::core
{
    class ImGuiWindow
    {

    public:
        ImGuiWindow()  {}
        ~ImGuiWindow() {}

        void init(GLFWwindow* window);

        void beginRender();
        void endRender();
        
        void shutdown();
    };
}