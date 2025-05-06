#pragma once

#include <string>
#include "Core/Base.h"
#include "Engine/Engine.h"
#include "Core/Context.h"


namespace VyEngine
{
    /// @brief Application Entry Point
    class Application : public Object
    {
    public:
        /// @brief Create the Engine in an uninitialized state.
        /// @param context 
        explicit Application(Context* context);

        /// @brief Setup before engine initialization. Can modify engine parameters.
        /// @brief Called by Application.
        /// @note Call ErrorExit() to terminate without initializing the engine.
        virtual void Setup() { }

        /// @brief Setup after engine initialization and before running the main-loop.
        /// @brief Called by Application.
        /// @note Call ErrorExit() to terminate without running the main-loop.
        virtual void Start() { }

        /// @brief Cleanup after the main-loop. 
        /// @brief Called by Application.
        virtual void Stop()  { }

        /// @brief Initialize the engine and run the main loop, then return the application exit code.
        /// @return Exit Code (EXIT_SUCCESS = 0, EXIT_FAILURE = 1)
        int Run();

        bool IsRunning() const;

        void ErrorExit();

    protected:
        // SharedPtr<Engine> m_Engine;

        int m_ExitCode;
    };


}