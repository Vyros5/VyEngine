#pragma once

#include "timer.hpp"
#include "event/events/app_event.hpp"
#include "event/event_handler.hpp"
#include "VyLib/vy_core.hpp"

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

        UniquePtr<Window>& GetWindow() { return mWindow; }

        static Application& GetApp() { return *sInstance; }
        static Telemetry& GetTelemetry() { return sTelemetry; }

        SharedPtr<CameraController> GetCameraController() const {return mCameraController; }

    protected:
        virtual void OnCreate()  { };
        virtual void OnDestroy() { };
        virtual void OnUpdate(float dt) { };
        virtual void OnRender(float dt) { };
        virtual void OnInput(float dt)  { };

        virtual void OnWindowResizeApp() { };

    private:
        void OnWindowClose(const Events::WindowCloseEvent& e);
        void OnWindowResize(const Events::WindowResizeEvent& e);

        void UpdateFPS(Timer& FPSCounter, const float elapsed, const float elapsedMs) const;

    protected:
        bool mRunning = false;
        
        UniquePtr<Window> mWindow = nullptr;
        SharedPtr<CameraController> mCameraController = nullptr;

    private:
        static Application* sInstance;
        static Telemetry sTelemetry;

        bool mPaused = false;

        Events::EventHandler<Events::WindowCloseEvent> mWindowCloseCallback;
        Events::EventHandler<Events::WindowResizeEvent> mWindowResizeCallback;
    };

    // Defined by CLIENT
    Application* CreateApplication();
}