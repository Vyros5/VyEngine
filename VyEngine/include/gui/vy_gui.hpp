#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glfw/glfw3.h>

class VyGUI
{
public:
    bool show_demo_window = true;
    void init(GLFWwindow* window, const char* glslVersion);
    void newFrame();
    virtual void update();
    void render();
    void shutdown();
};