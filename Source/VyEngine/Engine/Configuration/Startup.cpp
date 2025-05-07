#include "Engine/Configuration/Startup.h"

#include <deque>


namespace VyEngine
{
    void VyStartup::Startup(StartupStage stage)
    {
        if (stage == StartupStage::BASE)
        {
            
        }
        
        if (stage == StartupStage::CORE)
        {
            
            
            
        }
        
        std::deque<SubSystem*> SystemDeque;
        
        
    }
    
    void VyStartup::Shutdown(StartupStage stage)
    {
        
    }
}