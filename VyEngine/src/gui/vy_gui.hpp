#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


struct GLFWwindow;

namespace VyEngine
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