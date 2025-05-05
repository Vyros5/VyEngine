#pragma once

#include <Engine/Application.hpp>

namespace VyEditor
{
    class EditorApplication : public VyEngine::Application
    {
    public:
        explicit EditorApplication(VyEngine::Context* context);
        ~EditorApplication() override = default;
    };
}