#pragma once

#include "Support/Logger/LogDef.h"
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
        
        Engine();

        virtual ~Engine();
        
        /// @brief 
        /// @return 
        bool Init();

        void Exit();
        // void Run();

        void Update();

        void Render();


        bool IsRunning() const;

        // static bool OnEngineClosed(Events::EngineClosedEvent& event);

    private:

        bool m_Initialized { false };
    };
}