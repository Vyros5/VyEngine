#pragma once

#include <EnginePCH.h>

namespace Editor
{
    class EditorApplication : public VyApplication
    {
    public:
        EditorApplication(Context* context);
        ~EditorApplication();

        virtual void Run() override;
    };
}