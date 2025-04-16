#include "application.hpp"

#include "platform/Windows/base_window.hpp"
#include "event/event_manager.hpp"

namespace VyEngine
{
    Application* Application::sInstance = nullptr;
    Application::Telemetry Application::sTelemetry;

    Application::Application() :
        mRunning(true),
        mWindowCloseCallback([this](const Events::WindowCloseEvent& e) { OnWindowClose(e); }),
        mWindowResizeCallback([this](const Events::WindowResizeEvent& e) { OnWindowResize(e); })
    {
        sInstance = this;
        
        mWindow = Window::Create({ "VyEngine", 1280, 720, false, false });
        
        
        Events::Subscribe<Events::WindowCloseEvent>(mWindowCloseCallback);
        Events::Subscribe<Events::WindowResizeEvent>(mWindowResizeCallback);
    }


    Application::~Application()
    {
        OnDestroy();

        Events::gEventManager.Shutdown();
    }


    void Application::Run()
    {
        OnCreate();

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
            {
                
                OnInput(elapsedTime);
            
            }
            // Update ===================================
            {

                OnUpdate(elapsedTime);
            
            }
            // Dispatch Queued Events ===================================
            {
                Events::gEventManager.Dispatch();
            }
            // Render ===================================
            {

                OnRender(elapsedTime);

            }
            // Window Update ===================================
            {
                mWindow->OnUpdate();
            }
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
}