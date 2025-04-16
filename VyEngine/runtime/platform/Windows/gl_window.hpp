#pragma once

#include "base_window.hpp"

struct GLFWwindow;
struct GLFWmonitor;

namespace VyEngine
{
    class GraphicsContext;

    class OpenGLWindow : public Window
    {
    private:

        struct WindowData
        {
            std::string Title;
            std::uint16_t Width = 0;
            std::uint16_t Height = 0;
            bool Fullscreen = false;
            bool VSync = false;
        };

        GLFWwindow* mWindow = nullptr;
        GLFWmonitor* mMonitor = nullptr;

        UniquePtr<GraphicsContext> mContext;
        WindowData mData;

    public:
        OpenGLWindow(const WindowProps& props);
        ~OpenGLWindow() override;

        void OnUpdate() override;

        unsigned int GetWidth() const override { return mData.Width; }
        unsigned int GetHeight() const override { return mData.Height; }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void SetFullscreen(bool enabled) override;
        bool IsFullscreen() const override;

        void* GetNativeWindow() const override { return mWindow; }

    private:
        void Init(const WindowProps& props);
        void Shutdown();
    };
}