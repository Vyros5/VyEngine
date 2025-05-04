#include "Application.hpp"




namespace VyEditor
{
    Application::Application(Context* context) :
        VyObject(context)
    {
        m_Engine = MakeRef<Engine>(context);
    }

    Application::~Application() {}

    void Application::Run()
    {
        // Clock clock;

        // while (IsRunning())
        // {
            // m_Editor.PreUpdate();
            // m_Editor.Update(clock.GetDeltaTime());
            // m_Editor.PostUpdate();
            // clock.Update();
        // }

        if (!m_Engine->Init())
        {
            
        }
    }

    bool Application::IsRunning() const
    {
        return false;
        // return !m_Context.window->GetClose();
    }
}