#include "Engine/Engine.h"


namespace VyEngine
{
    Engine::Engine(Context* context) :
        VyObject(context),
        m_Initialized(false)
    {

    }

    Engine::~Engine() = default;

    bool Engine::Init()
    {
        if (m_Initialized) { return true; }

        VYTRACE("Initialized Engine")

        m_Initialized = true;
        return true;
    }

    void Engine::Run()
    {

    }

    void Engine::Exit()
    {

    }

    bool Engine::OnEngineClosed(Events::EngineClosedEvent& event)
    {
        return true;
    }
}