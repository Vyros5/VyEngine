#pragma once

#include <string>
#include <Core/Base.h>
#include <Engine/Engine.h>
#include <Core/Context.h>


using namespace VyEngine;

namespace VyEditor
{
    /// @brief VyEditor Entry Point
    class Application : public Object
    {
    public:
        //const std::string& projectName
        explicit Application(Context* context);



        // int Run();


        bool IsRunning() const;

        void ErrorExit();

    protected:

        SharedPtr<Engine> m_Engine;
        // Context m_Context;
        // Editor  m_Editor;
        int m_ExitCode;
    };
}