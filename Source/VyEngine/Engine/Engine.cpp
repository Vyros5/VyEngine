#include "Engine/Engine.h"


namespace VyEngine
{
    Engine::Engine(Context* context) :
        Object(context),
        m_Initialized(false)
    {
        VYTRACE("Created Engine")
    }

    Engine::~Engine() = default;

    bool Engine::Init()
    {
        if (m_Initialized) { return true; }

        VYTRACE("Initialized Engine")

        m_Initialized = true;
        return true;
    }

    // void Engine::Run()
    // {

    // }

    // void Engine::Exit()
    // {

    // }

    bool Engine::OnEngineClosed(Events::EngineClosedEvent& event)
    {
        return false;
    }
}