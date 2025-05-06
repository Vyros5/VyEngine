#include "Window/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "Core/Base.h"
#include "Event/Event.hpp"
#include "Event/EventDispatcher.hpp"
#include "Event/Events/EngineEvents.h"
#include "Engine/Engine.h"
#include "Render/Device/Device.h"

using namespace VyEngine::Events;

namespace VyEngine::Window
{
    Window::Window(const Render::Device& context, const Cfg::WindowConfig& config) :
        m_MaxSize{ config.maxWidth, config.maxHeight },
        m_MinSize{ config.minWidth, config.minHeight },
        m_Size{ config.width, config.height },
        m_Position{ config.x, config.y },
        m_RefreshRate(config.refreshRate),
        m_Fullscreen(config.fullscreen),
        m_CursorType(config.cursorType),
        m_CursorMode(config.cursorMode),
        m_Title(config.title),
        m_Device(context), 
        m_Config(config)
        {
            /* Create Window */
            CreateGlfwWindow(config);
    
            /* Cursor Settings */
            SetCursorMode(config.cursorMode);
            SetCursorType(config.cursorType);
    
    
        }
        
        Window::~Window()
        {
            glfwDestroyWindow(m_GlfwWindow);
        }
    
        // void Window::ForwardEventToLayers(Event& event)
        // {
        //     for (auto layer : m_Config.renderingLayers)
        //     {
        //         if (event.IsHandled()) { break; }
    
        //         layer->OnEvent(event);
        //     }
    
        //     for (auto layer : m_Config.overlayLayers)
        //     {
        //         if (event.IsHandled()) { break; }
    
        //         layer->OnEvent(event);
        //     }
        // }
    
        // void Window::Init(const VyEngine::WindowConfig& config)
        // {
        // }
    
    
        void Window::CreateGlfwWindow(const Cfg::WindowConfig& config)
        {
            GLFWmonitor* monitor = nullptr;
    
            if (m_Data.IsFullscreen) { monitor = glfwGetPrimaryMonitor(); }
        
            glfwWindowHint(GLFW_RESIZABLE,    config.resizable);
            glfwWindowHint(GLFW_DECORATED,    config.decorated);
            glfwWindowHint(GLFW_FOCUSED,      config.focused);
            glfwWindowHint(GLFW_MAXIMIZED,    config.maximized);
            glfwWindowHint(GLFW_FLOATING,     config.floating);
            glfwWindowHint(GLFW_VISIBLE,      config.visible);
            glfwWindowHint(GLFW_AUTO_ICONIFY, config.autoIconify);
            glfwWindowHint(GLFW_REFRESH_RATE, config.refreshRate);
            glfwWindowHint(GLFW_SAMPLES,      config.samples);
    
            m_GlfwWindow = glfwCreateWindow(
                m_Data.Width,
                m_Data.Height,
                m_Data.Title,
                monitor,
                nullptr
            );
    
            if (!m_GlfwWindow)
            {
                const char* pDesc = NULL;
                int err = glfwGetError(&pDesc);
                VYERROR("Failed to create GLFW Window: {0}\n{1}", pDesc, err);
                exit(EXIT_FAILURE);
            }
            else
            {
                UpdateSizeLimit();
                SetPosition(m_Position.first, m_Position.second);
                
    
                glfwSetWindowUserPointer(m_GlfwWindow, &m_Data);
    
                /* Callbacks */
                glfwSetFramebufferSizeCallback(m_GlfwWindow, __OnGlfwFrameBufferSizeChanged);
                
                glfwSetWindowCloseCallback(m_GlfwWindow, __OnGlfwWindowClose);
                glfwSetWindowSizeCallback(m_GlfwWindow, __OnGlfwWindowResized);
                glfwSetWindowMaximizeCallback(m_GlfwWindow, __OnGlfwWindowMaximized);
                glfwSetWindowIconifyCallback(m_GlfwWindow, __OnGlfwWindowMinimized);
    
                glfwSetMouseButtonCallback(m_GlfwWindow, __OnGlfwMouseButtonRaised);
                glfwSetScrollCallback(m_GlfwWindow, __OnGlfwMouseScrollRaised);
                glfwSetKeyCallback(m_GlfwWindow, __OnGlfwKeyboardRaised);
    
                glfwSetCursorPosCallback(m_GlfwWindow, __OnGlfwCursorMoved);
                glfwSetCharCallback(m_GlfwWindow, __OnGlfwTextInputRaised);
            }
        }
    
    
        void Window::MakeCurrentContext() const
        {
            glfwMakeContextCurrent(m_GlfwWindow);
        }
    
    
        void Window::SetCallbackFunction(const EventCallbackFn& callback)
        {
            m_Data.CallbackFn = callback;
        }
    
    
        void Window::SetClose(bool close) const
        {
            glfwSetWindowShouldClose(m_GlfwWindow, close);
        }
    
        bool Window::GetClose() const
        {
            return glfwWindowShouldClose(m_GlfwWindow);
        }
    
    
        void Window::SwapBuffers() const
        {
            glfwSwapBuffers(m_GlfwWindow);
        }
    
    
        void Window::OnUpdate(float dt)
        {
    
        }
    
        void Window::OnRender()
        {
    
        }
    
        bool Window::OnEvent(Event& event)
        {
            EventDispatcher dispatcher(event);
            
            dispatcher.Dispatch<KeyTypedEvent>(std::bind(&Window::OnKeyTyped, this, std::placeholders::_1));
            dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Window::OnKeyPressed, this, std::placeholders::_1));
            dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&Window::OnKeyReleased, this, std::placeholders::_1));
            
            dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Window::OnMouseMoved, this, std::placeholders::_1));
            dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Window::OnMouseScrolled, this, std::placeholders::_1));
            dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&Window::OnMouseButtonPressed, this, std::placeholders::_1));
            dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&Window::OnMouseButtonReleased, this, std::placeholders::_1));
    
            dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Window::OnWindowClosed, this, std::placeholders::_1));
            dispatcher.Dispatch<WindowResizedEvent>(std::bind(&Window::OnWindowResized, this, std::placeholders::_1));
            dispatcher.Dispatch<WindowRestoredEvent>(std::bind(&Window::OnWindowRestored, this, std::placeholders::_1));
            dispatcher.Dispatch<WindowMaximizedEvent>(std::bind(&Window::OnWindowMaximized, this, std::placeholders::_1));
            dispatcher.Dispatch<WindowMinimizedEvent>(std::bind(&Window::OnWindowMinimized, this, std::placeholders::_1));
    
            return true;
        }
    
    
    
        void Window::SetFullscreen(bool value)
        {
            if (value) { m_Data.IsFullscreen = true; }
    
            glfwSetWindowMonitor(
                m_GlfwWindow,
                value ? glfwGetPrimaryMonitor() : nullptr,
                static_cast<int>(m_Position.first),
                static_cast<int>(m_Position.second),
                static_cast<int>(m_Size.first),
                static_cast<int>(m_Size.second),
                m_RefreshRate
            );
    
            if (!value) { m_Data.IsFullscreen = false; }
        }
    
        bool Window::IsFullscreen() const
        {
            return m_Data.IsFullscreen;
        }
    
        void Window::ToggleFullscreen()
        {
            SetFullscreen(!m_Data.IsFullscreen);
        }
    
        void Window::UpdateSizeLimit() const
        {
            glfwSetWindowSizeLimits(
                m_GlfwWindow,
                static_cast<int>(m_MinSize.first),
                static_cast<int>(m_MinSize.second),
                static_cast<int>(m_MaxSize.first),
                static_cast<int>(m_MaxSize.second)
            );
        }
    
    
        #pragma region SETTINGS
    
            // ============================================================================================
            /* Title */
    
            void Window::SetTitle(const std::string& title)
            {
                m_Data.Title = title.c_str();
                m_Title = title;
                glfwSetWindowTitle(m_GlfwWindow, title.c_str());
            }
    
            std::string Window::GetTitle() const { return m_Title; }
    
            // ============================================================================================
            /* Refresh Rate */
    
            void Window::SetRefreshRate(int32_t refreshRate)
            {
                m_RefreshRate = refreshRate;
            }
    
            int32_t Window::GetRefreshRate() const { return m_RefreshRate; }
    
            // ============================================================================================
            /* Window Size */
    
            void Window::SetSize(uint16_t width, uint16_t height)
            {
                glfwSetWindowSize(m_GlfwWindow, static_cast<int>(width), static_cast<int>(height));
            }
    
            void Window::SetMinimumSize(int16_t minWidth, int16_t minHeight)
            {
                m_MinSize.first = minWidth;
                m_MinSize.second = minHeight;
                UpdateSizeLimit();
            }
    
            void Window::SetMaximumSize(int16_t maxWidth, int16_t maxHeight)
            {
                m_MaxSize.first = maxWidth;
                m_MaxSize.second = maxHeight;
                UpdateSizeLimit();
            }
            
            std::pair<uint16_t, uint16_t> Window::GetSize() const
            {
                int width, height;
                glfwGetWindowSize(m_GlfwWindow, &width, &height);
                return std::make_pair(static_cast<uint16_t>(width), static_cast<uint16_t>(height));
            }
    
            std::pair<int16_t, int16_t> Window::GetMinimumSize() const { return m_MinSize; }
    
            std::pair<int16_t, int16_t> Window::GetMaximumSize() const { return m_MaxSize; }
    
            // ============================================================================================
            /* FrameBuffer Size */
    
            std::pair<uint16_t, uint16_t> Window::GetFramebufferSize() const
            {
                int width, height;
                glfwGetFramebufferSize(m_GlfwWindow, &width, &height);
                return std::make_pair(static_cast<uint16_t>(width), static_cast<uint16_t>(height));
            }
    
            // ============================================================================================
            /* Position */
    
            void Window::SetPosition(int16_t X, int16_t Y)
            {
                glfwSetWindowPos(m_GlfwWindow, static_cast<int>(X), static_cast<int>(Y));
            }
    
            std::pair<int16_t, int16_t> Window::GetPosition() const
            {
                int x, y;
                glfwGetWindowPos(m_GlfwWindow, &x, &y);
                return std::make_pair(static_cast<uint16_t>(x), static_cast<uint16_t>(y)); 
            }
    
            // ============================================================================================
            /* Cursor */
    
            void Window::SetCursorPosition(int16_t X, int16_t Y)
            {
                glfwSetCursorPos(m_GlfwWindow, static_cast<double>(X), static_cast<double>(Y));
            }
    
            void Window::SetCursorType(ECursorType cursorType)
            {
                m_CursorType = cursorType;
                glfwSetCursor(m_GlfwWindow, m_Device.GetCursorInstance(cursorType));
            }
    
            ECursorType Window::GetCursorType() const
            {
                return m_CursorType;
            }
    
            void Window::SetCursorMode(ECursorMode cursorMode)
            {
                m_CursorMode = cursorMode;
                glfwSetInputMode(m_GlfwWindow, GLFW_CURSOR, static_cast<int>(cursorMode));
            }
    
            ECursorMode Window::GetCursorMode() const
            {
                return m_CursorMode;
            }
    
            // ============================================================================================
            /* Icon */
    
            void Window::SetIcon(const std::string& filePath)
            {
    
            }
    
            void Window::SetIconFromMemory(uint8_t* data, uint32_t width, uint32_t height)
            {
    
            }
    
        #pragma endregion
    
    
    
        #pragma region ACTION
    
            void Window::Minimize() const { glfwIconifyWindow(m_GlfwWindow);  }
    
            void Window::Maximize() const { glfwMaximizeWindow(m_GlfwWindow); }
    
            void Window::Restore() const  { glfwRestoreWindow(m_GlfwWindow);  }
    
            void Window::Hide() const     { glfwHideWindow(m_GlfwWindow); }
    
            void Window::Show() const     { glfwShowWindow(m_GlfwWindow); }
    
            void Window::Focus() const    { glfwFocusWindow(m_GlfwWindow); }
    
        #pragma endregion
    
    
    
        #pragma region BOOLEAN
    
            bool Window::IsHidden() const    { return glfwGetWindowAttrib(m_GlfwWindow, GLFW_VISIBLE)   == GLFW_FALSE; }
    
            bool Window::IsVisible() const   { return glfwGetWindowAttrib(m_GlfwWindow, GLFW_VISIBLE)   == GLFW_TRUE;  }
    
            bool Window::IsMaximized() const { return glfwGetWindowAttrib(m_GlfwWindow, GLFW_MAXIMIZED) == GLFW_TRUE;  }
    
            bool Window::IsMinimized() const { return glfwGetWindowAttrib(m_GlfwWindow, GLFW_MAXIMIZED) == GLFW_FALSE; }
    
            bool Window::IsFocused() const   { return glfwGetWindowAttrib(m_GlfwWindow, GLFW_FOCUSED)   == GLFW_TRUE;  }
    
            bool Window::IsResizable() const { return glfwGetWindowAttrib(m_GlfwWindow, GLFW_RESIZABLE) == GLFW_TRUE;  }
    
            bool Window::IsDecorated() const { return glfwGetWindowAttrib(m_GlfwWindow, GLFW_DECORATED) == GLFW_TRUE;  }
    
        #pragma endregion
    
    
    
    
    
    
        #pragma region CALLBACKS
    
            // ====================================================================================
    
            /* Window */
            void Window::__OnGlfwWindowClose(GLFWwindow* glWindow)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    WindowClosedEvent e;
                    data->CallbackFn(e);
                }
            }
    
            void Window::__OnGlfwWindowResized(GLFWwindow* glWindow, int width, int height)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    WindowResizedEvent e{static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
                    data->CallbackFn(e);
                }
            }
    
            void Window::__OnGlfwWindowMaximized(GLFWwindow* glWindow, int maximized)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    if (maximized == GLFW_TRUE)
                    {
                        WindowMaximizedEvent e;
                        data->CallbackFn(e);
                        return;
                    }
    
                    WindowRestoredEvent e;
                    data->CallbackFn(e);
                }
            }
    
            void Window::__OnGlfwWindowMinimized(GLFWwindow* glWindow, int minimized)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    if (minimized == GLFW_TRUE)
                    {
                        WindowMinimizedEvent e;
                        data->CallbackFn(e);
                        return;
                    }
    
                    WindowRestoredEvent e;
                    data->CallbackFn(e);
                }
            }
    
    
            /* Keyboard */
            void Window::__OnGlfwKeyboardRaised(GLFWwindow* glWindow, int key, int scancode, int action, int mods)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                
                if (!data) { return; }
    
                if (action == GLFW_PRESS)
                {
                    KeyPressedEvent e{static_cast<Data::EKeyCode>(key), 0};
                    data->CallbackFn(e);
                }
                
                if (action == GLFW_RELEASE)
                {
                    KeyReleasedEvent e{static_cast<Data::EKeyCode>(key)};
                    data->CallbackFn(e);
                }
        
                if (action == GLFW_REPEAT)
                {
                    KeyPressedEvent e{static_cast<Data::EKeyCode>(key), 0};
                    data->CallbackFn(e);
                }
    
                if (key == GLFW_KEY_ESCAPE)
                {
                    WindowClosedEvent e;
                    data->CallbackFn(e);
                }
            }
    
            void Window::__OnGlfwTextInputRaised(GLFWwindow* glWindow, unsigned int character)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    std::string arr;
                    arr.append(1, character);
                    KeyTypedEvent e{arr.c_str()};
                    data->CallbackFn(e);
                }
            }
    
    
            /* Mouse */
            void Window::__OnGlfwMouseButtonRaised(GLFWwindow* glWindow, int button, int action, int mods)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    if (action == GLFW_PRESS)
                    {
                        MouseButtonPressedEvent e{static_cast<Data::EMouseCode>(button)};
                        data->CallbackFn(e);
                        return;
                    }
    
                    MouseButtonReleasedEvent e{static_cast<Data::EMouseCode>(button)};
                    data->CallbackFn(e);
                }
            }
    
            void Window::__OnGlfwMouseScrollRaised(GLFWwindow* glWindow, double xOffset, double yOffset)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    MouseScrolledEvent e{xOffset, yOffset};
                    data->CallbackFn(e);
                }
            }
    
            void Window::__OnGlfwCursorMoved(GLFWwindow* glWindow, double xPos, double yPos)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    MouseMovedEvent e{xPos, yPos};
                    // data->CallbackFn(e);
                }
            }
    
    
            /* FrameBuffer */
            void Window::__OnGlfwFrameBufferSizeChanged(GLFWwindow* glWindow, int width, int height)
            {
                WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                if (data)
                {
                    data->SetWidth(width);
                    data->SetHeight(height);
    
                    VYINFO("FrameBuffer size changed: {0}, {1}", data->Width, data->Height);
                }
            }
    
            // ========================================================================================
    
            bool Window::OnWindowClosed(VyEngine::Events::WindowClosedEvent& event)
            {
                glfwSetWindowShouldClose(m_GlfwWindow, GLFW_TRUE);
                VYINFO("Window has been closed");
    
                EngineClosedEvent e(event.GetName());
                EventDispatcher dispatcher(e);
                dispatcher.Dispatch<EngineClosedEvent>(std::bind(&VyEngine::Engine::OnEngineClosed, std::placeholders::_1));
                return true;
            }
    
            bool Window::OnWindowResized(VyEngine::Events::WindowResizedEvent& event)
            {
                VYINFO("Window has been resized");
    
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::WindowResizedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return false;
            }
    
            bool Window::OnWindowRestored(VyEngine::Events::WindowRestoredEvent& event)
            {
                VYINFO("Window has been restored");
    
                m_Data.IsMinimized = false;
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::WindowResizedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return false;
            }
    
            bool Window::OnWindowMinimized(VyEngine::Events::WindowMinimizedEvent& event)
            {
                VYINFO("Window has been minimized");
    
                m_Data.IsMinimized = true;
                m_Data.IsMaximized = false;
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::WindowResizedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return false;
            }
    
            bool Window::OnWindowMaximized(VyEngine::Events::WindowMaximizedEvent& event)
            {
                VYINFO("Window has been maximized");
                return false;
            }
    
            // ========================================================================================
    
            bool Window::OnKeyPressed(VyEngine::Events::KeyPressedEvent& event)
            {
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::KeyPressedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return true;
            }
    
            bool Window::OnKeyReleased(VyEngine::Events::KeyReleasedEvent& event)
            {
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::KeyReleasedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return true;
            }
    
            bool Window::OnKeyTyped(VyEngine::Events::KeyTypedEvent& event)
            {
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::KeyTypedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return true;
            }
    
    
            bool Window::OnMouseMoved(VyEngine::Events::MouseMovedEvent& event)
            {
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::MouseMovedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return true;
            }
    
            bool Window::OnMouseScrolled(VyEngine::Events::MouseScrolledEvent& event)
            {
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::MouseScrolledEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return true;
            }
    
            bool Window::OnMouseButtonPressed(VyEngine::Events::MouseButtonPressedEvent& event)
            {
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::MouseButtonPressedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return true;
            }
    
            bool Window::OnMouseButtonReleased(VyEngine::Events::MouseButtonReleasedEvent& event)
            {
                EventDispatcher dispatcher(event);
                dispatcher.ForwardTo<VyEngine::Events::MouseButtonReleasedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
                return true;
            }
    
        #pragma endregion
}