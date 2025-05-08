#pragma once

#include "defines.h"
#include "Core/Base.h"
#include "Core/Context.h"


namespace VyEngine
{
    class VyApplication
    {
    public:
        /// @brief Constructor - Application not yet initialized.
        VyApplication(Context* context);

        /// @brief Virtual Destructor.
        virtual ~VyApplication();

        VyApplication(const VyApplication& other) = delete;
        VyApplication(VyApplication&& other)      = delete;

        /// @brief Called before any engine initialization.
        /// Can be overridden to be able to configure sub-systems before they are initialized. 
        // virtual void PreCoreStartup() {} //;

        /// @brief Called after engine initialization.
        /// Can be overridden to do additional application specific initialization.
        // virtual void PostCoreStartup() {}

        /// @brief Called before any engine initialization.
        /// Can be overridden to do application specific deinitialization that still requires a running engine.
        // virtual void PreCoreShutdown() {}

        /// @brief Called after all systems have been shutdown.
        // virtual void PostCoreShutdown() {}


        /// @brief Initialize the engine and run the main loop, then return the application exit code.
        /// Must be overridden.
        /// @return Exit Code (EXIT_SUCCESS = 0, EXIT_FAILURE = 1)
        virtual void Run() = 0;

        // void OnEvent(Event& e);

    //     inline void SetReturnCode(i32 returnCode) { m_ReturnCode = returnCode; }

    //     inline i32 GetReturnCode() const { return m_ReturnCode; }

    //     /// @brief Returns the only instance of the application.
    //     /// @return VyApplication*
        static VyApplication* GetInstance() { return s_AppInstance; }

    //     /// @brief Static function that requests that the application quits after the current invocation of Run() finishes.
    //     // virtual void RequestQuit();
        static VyApplication* s_AppInstance;
        
        // inline bool ShouldQuit() const { return m_QuitRequested; }

        bool Isrunning() const;

    private:

        // bool m_Running;

    protected:

        Context* m_Context;
    };
}