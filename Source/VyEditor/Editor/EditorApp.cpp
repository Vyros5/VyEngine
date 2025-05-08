#include "Editor/EditorApp.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Editor
{
    EditorApplication::EditorApplication(Context* context) : 
        VyApplication(context)
    {
        VYTRACE("Created EditorApplication")
        InitImGui();
    }

    EditorApplication::~EditorApplication()
    {
        ShutdownImGui();
        VYTRACE("Destroyed EditorApplication")
    }

    void EditorApplication::Run()
    {
        VYTRACE("Start Run")

        while (Isrunning())
        {
            PreUpdate();
            Update();
            Render();
        }

        VYTRACE("End Run")
    }

    void EditorApplication::InitImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        // io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        // io.ConfigWindowsResizeFromEdges  = true;
        // io.ConfigViewportsNoTaskBarIcon  = true;
        // io.ConfigViewportsNoDecoration   = true;

        windowFlags = 0x0;
        // windowFlags |= ImGuiWindowFlags_NoDocking;
        // windowFlags |= ImGuiWindowFlags_NoTitleBar;
        // windowFlags |= ImGuiWindowFlags_NoCollapse;
        // windowFlags |= ImGuiWindowFlags_NoResize;
        // windowFlags |= ImGuiWindowFlags_NoMove;
        // windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        // windowFlags |= ImGuiWindowFlags_NoNavFocus;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_Context->window->GetGlfwWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 450");
    }

    void EditorApplication::ShutdownImGui()
    {
        if (ImGui::GetCurrentContext())
        {
            ImGui_ImplGlfw_Shutdown();
            ImGui_ImplOpenGL3_Shutdown();
            ImGui::DestroyContext();
        }
    }

    void EditorApplication::PreUpdate()
    {
        m_Context->displayDevice->PollEvents();

        // Start ImGUI Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Demo
        if (m_ShowDemo)
        {
            ImGui::ShowDemoWindow();
        }


    }

    void EditorApplication::Update()
    {

    }

    void EditorApplication::Render()
    {
        ImGui::Render();
        
        // std::pair<u16, u16> fbSize = m_Context->window->GetFramebufferSize();
        // m_Context->gfxDriver->SetViewport(100,100, static_cast<u32>(fbSize.first), static_cast<u32>(fbSize.second));

        m_Context->gfxDriver->ClearBuffer(true, true, false);

        // Render Draw Data
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_Context->window->SwapBuffers();
    }
}