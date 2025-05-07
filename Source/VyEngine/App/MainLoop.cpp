// #include "App/App.h"
// #include "Engine/Configuration/Startup.h"

// using namespace VyEngine;

// bool VyRun_Startup(VyApplication* appInstance)
// {
//     // Set App Instance pointer.
//     VyApplication::s_AppInstance = appInstance;

//     // appInstance->PreCoreStartup();
//     // VyStartup::StartCore();
//     // appInstance->PostCoreStartup();
//     return true;
// }


// void VyRun_MainLoop(VyApplication* appInstance)
// {
//     while (appInstance->Isrunning())
//     {
//         appInstance->Run();
//     }
// }


// void VyRun_Shutdown(VyApplication* appInstance)
// {
//     // High Level


//     // Core Level
//     // {
//     //     appInstance->PreCoreShutdown();
//     //     VyStartup::ShutdownCore();
//     //     appInstance->PostCoreShutdown();
//     // }
    
//     // Reset App instance pointer.
//     VyApplication::s_AppInstance = nullptr;
// }

// void VyRun(VyApplication* appInstance)
// {
//     if (VyRun_Startup(appInstance))
//     {
//         VyRun_MainLoop(appInstance);
//     }

//     VyRun_Shutdown(appInstance);
// }