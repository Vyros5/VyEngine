#pragma once

#include <Engine/Application.h>

namespace VyEditor
{
    class EditorApplication : public VyEngine::Application
    {
    public:
        explicit EditorApplication(VyEngine::Context* context);
        ~EditorApplication() = default;
    };
}