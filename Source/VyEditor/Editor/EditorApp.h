#pragma once

#include <EnginePCH.h>
#include <imgui.h>

namespace Editor
{
    class EditorApplication : public VyApplication
    {
    public:
        EditorApplication(Context* context);
        ~EditorApplication();

        virtual void Run() override;

        void InitImGui();
        
        void ShutdownImGui();

        void PreUpdate();

        void Update();

        void Render();

        

    private:

        ImGuiWindowFlags windowFlags;

        bool m_ShowDemo = true;
    };
}