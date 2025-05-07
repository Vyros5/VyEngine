#pragma once

#include "defines.h"


namespace VyEngine
{
    enum StartupStage : i8
    {
        NONE = -1,
        BASE,
        CORE,
        
        COUNT
    };
    
    
    class SubSystem
    {
    public:
        SubSystem()
        {
            for (i32 i = 0; i < StartupStage::COUNT; ++i)
            {
                m_StartupComplete[i] = false;
            }
        }
        
        virtual ~SubSystem() = default;
        
    private:
        
        friend class VyStartup;
        
        virtual void OnBaseSystemsStart() {}
        
        
        virtual void OnCoreSystemsStart() {}
        
        
        virtual void OnCoreSystemsShutdown() {}
        
        b8 m_StartupComplete[StartupStage::COUNT];
    };
}