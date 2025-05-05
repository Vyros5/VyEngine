#include "Engine/Application.hpp"




namespace VyEngine
{
    Application::Application(Context* context) : 
        Object(context),
        m_ExitCode(EXIT_SUCCESS)
    {
        m_Engine = new Engine(context);
    }


    int Application::Run()
    {
        if (m_ExitCode)
        {
            return m_ExitCode;
        }

        if (!m_Engine->Init())
        {
            ErrorExit();
            return m_ExitCode;
        }

        return m_ExitCode;
    }

    bool Application::IsRunning() const
    {
        return false;
        // return !m_Context.window->GetClose();
    }

    void Application::ErrorExit()
    {
        // m_Engine->Exit();
        m_ExitCode = EXIT_FAILURE;
    }
}