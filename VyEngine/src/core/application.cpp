#include "application.hpp"

#include "camera/camera_controller.hpp"
#include "platform/Windows/base_window.hpp"
#include "event/event_manager.hpp"

namespace VyEngine
{
    // std::unique_ptr<Application> Application::sInstance = nullptr;
    Application* Application::sInstance = nullptr;
    Application::Telemetry Application::sTelemetry;

    Application::Application() :
        mRunning(true),
        mWindowCloseCallback([this](const Events::WindowCloseEvent& e) { OnWindowClose(e); }),
        mWindowResizeCallback([this](const Events::WindowResizeEvent& e) { OnWindowResize(e); })
    {
        // Start Logger
        Log::Initialize();
        Log::CoreTrace("VyEngine Initialization.");


        sInstance = this;
        
        // Create Window
        mWindow = Window::Create({ "VyEngine", 1280, 720, false, false });
        
        // Initialize Renderers
        mRenderer.Init(mWindow->GetWidth(), mWindow->GetHeight());
        
        // Subscribe to events
        Events::Subscribe<Events::WindowCloseEvent>(mWindowCloseCallback);
        Events::Subscribe<Events::WindowResizeEvent>(mWindowResizeCallback);
    }

    // Application& Application::GetApp()
    // {
    //     if (!sInstance)
    //     {
    //         sInstance = std::make_unique<Application>();
    //     }
    //     return *instance;
    // }

    static std::unique_ptr<Application> instance = nullptr;

    Application& Application::getInstance()
    {
        if (!instance)
        {
            instance = std::make_unique<Application>();
        }

        return *instance;
    }


    Application::~Application()
    {
        // OnDestroy();
        
        Events::gEventManager.Shutdown();

        Log::CoreTrace("Engine Shutdown.");
        Log::Delete();
    }


    void Application::Run()
    {
        // OnCreate();

        Timer timer;
        Timer timerFPSCounter;

        while (mRunning)
        {
            if (mPaused)
            {
                mWindow->OnUpdate();
            }

            // Time ===================================
            
            const float elapsedTimeMs = timer.ElapsedMs();
            const float elapsedTime = elapsedTimeMs * 0.001f;
            timer.Restart();

            UpdateFPS(timerFPSCounter, elapsedTime, elapsedTimeMs);
            
            // Input ===================================
            
                
            // OnProcessInput(elapsedTime);
            
            
            // Update ===================================
            

            // OnUpdate(elapsedTime);
            
            
            // Dispatch Queued Events ===================================
            
            Events::gEventManager.Dispatch();
            
            // Render ===================================

            mRenderer.BeginScene(mCameraController);
            // OnRender(elapsedTime);
            mRenderer.EndScene();

            
            // Window Update ===================================
            
            mWindow->OnUpdate();
            
        }
    }


    void Application::OnWindowClose(const Events::WindowCloseEvent& e)
    {
        mRunning = false;
    }


    void Application::OnWindowResize(const Events::WindowResizeEvent& e)
    {
        if (e.width == 0 || e.height == 0)
        {
            mPaused = true;
            return;
        }

        mPaused = false;
    }


    void Application::UpdateFPS(Timer& FPSCounter, const float elapsed, const float elapsedMs) const
    {
        static float accumTime = 0.0f;
        static float accumTimeMs = 0.0f;
        static float accumFrameCount = 0.0f;

        if (FPSCounter.ElapsedMs() > 1000.0f)
        {
            sTelemetry.frameTime = accumTimeMs / accumFrameCount;
            sTelemetry.fps = accumFrameCount / accumTime;

            FPSCounter.Restart();
            accumTime = 0.0f;
            accumTimeMs = 0.0f;
            accumFrameCount = 0.0f;
        }
        else
        {
            accumTime += elapsed;
            accumTimeMs += elapsedMs;
            accumFrameCount += 1.0f;
        }
    }
}