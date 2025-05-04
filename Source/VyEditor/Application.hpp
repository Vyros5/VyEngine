#pragma once

#include <string>
#include <Core/Base.h>
#include <Engine/Engine.h>
#include <Core/Context.h>

using namespace VyEngine;
using namespace VyEngine::Core;

namespace VyEditor
{
    /// @brief VyEditor Entry Point
    class Application : public VyObject
    {
    public:
        //const std::string& projectName
        explicit Application(Context* context);


        ~Application();


        void Run();


        bool IsRunning() const;

    private:
        Ref<Engine> m_Engine;
        // Context m_Context;
        // Editor  m_Editor;
    };
}