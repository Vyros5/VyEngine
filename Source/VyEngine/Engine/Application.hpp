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
        explicit Application(Context* context);

        int Run();


        bool IsRunning() const;

        void ErrorExit();

    protected:
        SharedPtr<Engine> m_Engine;

        int m_ExitCode;
    };


}