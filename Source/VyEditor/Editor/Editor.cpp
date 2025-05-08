// #include "Editor/Editor.h"

// #include <Core/Context.h>

// #include <imgui_impl_glfw.h>
// #include <imgui_impl_opengl3.h>

// namespace Editor
// {
    // VyEditor::VyEditor(VyEngine::Context* context)
    // {
    //     IMGUI_CHECKVERSION();

    //     ImGui::CreateContext();

    //     ImGuiIO& io = ImGui::GetIO();
    //     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //     io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //     io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    //     io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    //     io.ConfigWindowsResizeFromEdges  = true;
    //     // io.ConfigViewportsNoTaskBarIcon  = true;
    //     // io.ConfigViewportsNoDecoration   = true;

    //     windowFlags = 0x0;
    //     windowFlags |= ImGuiWindowFlags_NoDocking;
    //     windowFlags |= ImGuiWindowFlags_NoTitleBar;
    //     windowFlags |= ImGuiWindowFlags_NoCollapse;
    //     windowFlags |= ImGuiWindowFlags_NoResize;
    //     windowFlags |= ImGuiWindowFlags_NoMove;
    //     windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    //     windowFlags |= ImGuiWindowFlags_NoNavFocus;

    //     ImGui_ImplGlfw_InitForOpenGL(context->window->GetGlfwWindow(), true);
    //     ImGui_ImplOpenGL3_Init("#version 450");


    // }

    // VyEditor::~VyEditor()
    // {
    //     if (ImGui::GetCurrentContext())
    //     {
    //         ImGui_ImplGlfw_Shutdown();
    //         ImGui_ImplOpenGL3_Shutdown();
    //         ImGui::DestroyContext();
    //     }
    // }




// }