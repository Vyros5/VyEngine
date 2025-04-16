#pragma once

#include "vy_core.hpp"
#include <string>

namespace VyEngine
{
    struct WindowProps
    {
    public:
        std::string Title;
        unsigned int Width = 0;
        unsigned int Height = 0;
        bool IsFullscreen = false;
        bool IsVSync = false;

        WindowProps(
            const std::string& title = "VyEngine",
            unsigned int width       = 1280,
            unsigned int height      = 720,
            bool isFullscreen        = false,
            bool isVSync             = false
        ) :
        Title(title),
        Width(width),
        Height(height),
        IsFullscreen(isFullscreen),
        IsVSync(isVSync)
        {}
    };


    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void SetFullscreen(bool enabled) = 0;
        virtual bool IsFullscreen() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static UniquePtr<Window> Create(const WindowProps& props = WindowProps());
    };
}