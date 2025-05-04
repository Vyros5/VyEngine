#pragma once

#include "Support/Logger/LogDef.h"
#include "Event/Events/EngineEvents.h"
#include "Core/VyObject/VyObject.h"
#include "Window/Window.h"

namespace VyEngine
{
    /**
     *  VyEngine Engine
     */
    class Engine : public VyObject
    {
    public:
        explicit Engine(Context* context);

        ~Engine() override;
        
        bool Init();
        void Exit();
        void Run();

        static bool OnEngineClosed(Events::EngineClosedEvent& event);

    private:

        bool m_Initialized { false };
    };
}