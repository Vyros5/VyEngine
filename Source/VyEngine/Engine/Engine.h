#pragma once

#include "Support/Logger/LogDef.h"
#include "Event/Events/EngineEvents.h"
#include "Core/Object/Object.h"
#include "Window/Window.h"

namespace VyEngine
{
    /**
     *  VyEngine Engine
     */
    class Engine : public Object
    {
    public:
        explicit Engine(Context* context);

        ~Engine() override;
        
        bool Init();
        // void Exit();
        // void Run();

        static bool OnEngineClosed(Events::EngineClosedEvent& event);

    private:

        bool m_Initialized { false };
    };
}