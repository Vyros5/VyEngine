#pragma once

#include "timer.hpp"
#include "event/events/app_event.hpp"
#include "event/event_handler.hpp"
#include "VyLib/vy_core.hpp"
#include "VyLib/vy_logger.hpp"
#include "render/renderer.hpp"

namespace VyEngine
{
    class Window;
    class CameraController;


    class Application
    {
    private:
        struct Telemetry
        {
            float frameTime = 0.0f;
            float fps = 0.0f;
        };

    public:
        Application();
        virtual ~Application();

        Application(const Application&) = delete;
        const Application& operator=(const Application&) = delete;

        void Run();

        static Application& getInstance();

        UniquePtr<Window>& GetWindow() { return mWindow; }
        static Application& GetApp() { return *sInstance; }

        static Telemetry& GetTelemetry() { return sTelemetry; }

        SharedPtr<CameraController> GetCameraController() const {return mCameraController; }

        Renderer& GetRenderer() { return mRenderer; }

    protected:

        // virtual void OnCreate();
        // virtual void OnDestroy();
        // virtual void OnUpdate(float dt);
        // virtual void OnRender(float dt);
        // virtual void OnProcessInput(float dt);

        // void OnWindowResizeApp() ;

    private:
        void OnWindowClose(const Events::WindowCloseEvent& e);
        void OnWindowResize(const Events::WindowResizeEvent& e);

        void UpdateFPS(Timer& FPSCounter, const float elapsed, const float elapsedMs) const;

    protected:
        bool mRunning = false;
        
        SharedPtr<CameraController> mCameraController = nullptr;
        UniquePtr<Window> mWindow = nullptr;
        Renderer mRenderer;

    private:
        static Application* sInstance;
        static Telemetry sTelemetry;

        bool mPaused = false;

        Events::EventHandler<Events::WindowCloseEvent> mWindowCloseCallback;
        Events::EventHandler<Events::WindowResizeEvent> mWindowResizeCallback;
    };

    // Defined by CLIENT
    UniquePtr<Application> CreateApplication();
}