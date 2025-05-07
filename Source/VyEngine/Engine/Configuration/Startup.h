#pragma once

#include "Engine/Configuration/SubSystem.h"

namespace VyEngine
{
    class VyStartup
    {
        public:
        
        static void StartBase() { Startup(StartupStage::BASE); }
        
        
        static void StartCore() { Startup(StartupStage::CORE); }
        
        
        static void ShutdownBase() { Shutdown(StartupStage::BASE); }
        
        
        static void ShutdownCore() { Shutdown(StartupStage::CORE); }
        
        
        private:
        
        static void Startup(StartupStage stage);
        
        static void Shutdown(StartupStage stage);
        
        
        static StartupStage s_CurrentStage;
    };
}