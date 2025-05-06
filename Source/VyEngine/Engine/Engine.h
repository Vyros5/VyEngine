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

        ~Engine();
        
        /// @brief 
        /// @return 
        bool Init();

        void Exit();
        // void Run();

        bool IsRunning() const;

        static bool OnEngineClosed(Events::EngineClosedEvent& event);

    private:

        bool m_Initialized { false };
    };
}