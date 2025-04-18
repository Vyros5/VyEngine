#include "vy_gui.hpp"

#include <glfw/glfw3.h>

namespace VyEngine
{
    void ImGuiWindow::init(GLFWwindow* window)
    {
        // Setup Dear ImGui context.
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io         = ImGui::GetIO();

        io.ConfigFlags     |= ImGuiConfigFlags_NavEnableKeyboard;
        // io.ConfigFlags     |= ImGuiConfigFlags_NoMouseCursorChange;

        // Setup platform rendering bindings.
        if(!ImGui_ImplGlfw_InitForOpenGL(window, true))
        {
            std::cout << "Failed to init ImGui_ImplGlfw_InitForOpenGL\n";
        }
        if (!ImGui_ImplOpenGL3_Init("#version 450"))
        {
            std::cout << "Failed to init ImGui_ImplOpenGL3\n";
        }

        // Set Style
        ImGui::StyleColorsDark();
    }

    void ImGuiWindow::beginRender()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiWindow::endRender()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiWindow::shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

    }
}