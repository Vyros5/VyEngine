#include "Window/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "Core/Base.h"
#include "Render/Device/Device.h"

using namespace VyEngine::Evt;

std::unordered_map<GLFWwindow*, VyEngine::Window::Window*> VyEngine::Window::Window::__WINDOWS_MAP;

namespace VyEngine::Window
{
    Window::Window(const Display::Device& device, const Cfg::WindowConfig& config) :
        m_MaxSize{ config.maxWidth, config.maxHeight },
        m_MinSize{ config.minWidth, config.minHeight },
        m_Size{ config.width, config.height },
        m_Position{ config.x, config.y },
        m_RefreshRate(config.refreshRate),
        m_Fullscreen(config.fullscreen),
        m_CursorType(config.cursorType),
        m_CursorMode(config.cursorMode),
        m_Title(config.title),
        m_Device(device), 
        m_Config(config)
        {
            /* Create Window */
            CreateGlfwWindow(config);
    
            /* Cursor Settings */
            SetCursorMode(config.cursorMode);
            SetCursorType(config.cursorType);
    
            /* Callback binding */
            BindKeyCallback();
            BindMouseCallback();
            BindScrollCallback();
            BindIconifyCallback();
            BindCloseCallback();
            BindResizeCallback();
            BindCursorMoveCallback();
            BindFramebufferResizeCallback();
            BindMoveCallback();
            BindFocusCallback();

            /* Event listening */
            ResizeEvent.AddListener(std::bind(&Window::OnResize, this, std::placeholders::_1, std::placeholders::_2));
            MoveEvent.AddListener(std::bind(&Window::OnMove, this, std::placeholders::_1, std::placeholders::_2));
        }
        
        Window::~Window()
        {
            glfwDestroyWindow(m_GlfwWindow);
        }
    
    
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
                i32 err = glfwGetError(&pDesc);
                VYERROR("Failed to create GLFW Window: {0}\n{1}", pDesc, err);
                exit(EXIT_FAILURE);
            }
            else
            {
                UpdateSizeLimit();
                SetPosition(m_Position.first, m_Position.second);
                
    
                glfwSetWindowUserPointer(m_GlfwWindow, &m_Data);
    
                __WINDOWS_MAP[m_GlfwWindow] = this;

                VYINFO("Successfully created new GLFW Window: {}", __WINDOWS_MAP.size())
            }
        }
    
    
        void Window::MakeCurrentContext() const
        {
            glfwMakeContextCurrent(m_GlfwWindow);
        }
    
    
        Window* Window::FindInstance(GLFWwindow* glfwWindow)
        {
            return __WINDOWS_MAP.find(glfwWindow) != __WINDOWS_MAP.end() ? __WINDOWS_MAP[glfwWindow] : nullptr;
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
    

        void Window::SetFullscreen(bool value)
        {
            if (value) { m_Data.IsFullscreen = true; }
    
            glfwSetWindowMonitor(
                m_GlfwWindow,
                value ? glfwGetPrimaryMonitor() : nullptr,
                static_cast<i32>(m_Position.first),
                static_cast<i32>(m_Position.second),
                static_cast<i32>(m_Size.first),
                static_cast<i32>(m_Size.second),
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
                static_cast<i32>(m_MinSize.first),
                static_cast<i32>(m_MinSize.second),
                static_cast<i32>(m_MaxSize.first),
                static_cast<i32>(m_MaxSize.second)
            );
        }
    
    
        #pragma region SETTINGS
    
            // ============================================================================================
            /* Title */
    
            void Window::SetTitle(const VyString& title)
            {
                m_Data.Title = title.c_str();
                m_Title = title;
                glfwSetWindowTitle(m_GlfwWindow, title.c_str());
            }
    
            VyString Window::GetTitle() const { return m_Title; }
    
            // ============================================================================================
            /* Refresh Rate */
    
            void Window::SetRefreshRate(i32 refreshRate)
            {
                m_RefreshRate = refreshRate;
            }
    
            i32 Window::GetRefreshRate() const { return m_RefreshRate; }
    
            // ============================================================================================
            /* Window Size */
    
            void Window::SetSize(u16 width, u16 height)
            {
                glfwSetWindowSize(m_GlfwWindow, static_cast<i32>(width), static_cast<i32>(height));
            }
    
            void Window::SetMinimumSize(i16 minWidth, i16 minHeight)
            {
                m_MinSize.first = minWidth;
                m_MinSize.second = minHeight;
                UpdateSizeLimit();
            }
    
            void Window::SetMaximumSize(i16 maxWidth, i16 maxHeight)
            {
                m_MaxSize.first = maxWidth;
                m_MaxSize.second = maxHeight;
                UpdateSizeLimit();
            }
            
            std::pair<u16, u16> Window::GetSize() const
            {
                i32 width, height;
                glfwGetWindowSize(m_GlfwWindow, &width, &height);
                return std::make_pair(static_cast<u16>(width), static_cast<u16>(height));
            }
    
            std::pair<i16, i16> Window::GetMinimumSize() const { return m_MinSize; }
    
            std::pair<i16, i16> Window::GetMaximumSize() const { return m_MaxSize; }
    
            // ============================================================================================
            /* FrameBuffer Size */
    
            std::pair<u16, u16> Window::GetFramebufferSize() const
            {
                i32 width, height;
                glfwGetFramebufferSize(m_GlfwWindow, &width, &height);
                return std::make_pair(static_cast<u16>(width), static_cast<u16>(height));
            }
    
            // ============================================================================================
            /* Position */
    
            void Window::SetPosition(i16 X, i16 Y)
            {
                glfwSetWindowPos(m_GlfwWindow, static_cast<i32>(X), static_cast<i32>(Y));
            }
    
            std::pair<i16, i16> Window::GetPosition() const
            {
                i32 x, y;
                glfwGetWindowPos(m_GlfwWindow, &x, &y);
                return std::make_pair(static_cast<u16>(x), static_cast<u16>(y)); 
            }
    
            // ============================================================================================
            /* Cursor */
    
            void Window::SetCursorPosition(i16 X, i16 Y)
            {
                glfwSetCursorPos(m_GlfwWindow, static_cast<f64>(X), static_cast<f64>(Y));
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
                glfwSetInputMode(m_GlfwWindow, GLFW_CURSOR, static_cast<i32>(cursorMode));
            }
    
            ECursorMode Window::GetCursorMode() const
            {
                return m_CursorMode;
            }
    
            // ============================================================================================
            /* Icon */
    
            void Window::SetIcon(const VyString& filePath)
            {
    
            }
    
            void Window::SetIconFromMemory(u8* data, u32 width, u32 height)
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
    
    
    
        void Window::BindKeyCallback() const
        {
            auto keyCallback = [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
            {
                Window* windowInstance = FindInstance(p_window);
        
                if (windowInstance)
                {
                    if (p_action == GLFW_PRESS)
                        windowInstance->KeyPressedEvent.Invoke(p_key);
        
                    if (p_action == GLFW_RELEASE)
                        windowInstance->KeyReleasedEvent.Invoke(p_key);
                }
            };
        
            glfwSetKeyCallback(m_GlfwWindow, keyCallback);
        }
    
        void Window::BindMouseCallback() const
        {
            auto mouseCallback = [](GLFWwindow* p_window, int p_button, int p_action, int p_mods)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    if (p_action == GLFW_PRESS)
                        windowInstance->MouseButtonPressedEvent.Invoke(p_button);

                    if (p_action == GLFW_RELEASE)
                        windowInstance->MouseButtonReleasedEvent.Invoke(p_button);
                }
            };

            glfwSetMouseButtonCallback(m_GlfwWindow, mouseCallback);
        }

        void Window::BindScrollCallback() const
        {
            auto scrollCallback = [](GLFWwindow* p_window, double p_xOffset, double p_yOffset)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->MouseScrollEvent.Invoke(p_xOffset, p_yOffset);
                }
            };

            glfwSetScrollCallback(m_GlfwWindow, scrollCallback);
        }

        void Window::BindResizeCallback() const
        {
            auto resizeCallback = [](GLFWwindow* p_window, int p_width, int p_height)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->ResizeEvent.Invoke(static_cast<uint16_t>(p_width), static_cast<uint16_t>(p_height));
                }
            };

            glfwSetWindowSizeCallback(m_GlfwWindow, resizeCallback);
        }

        void Window::BindFramebufferResizeCallback() const
        {
            auto framebufferResizeCallback = [](GLFWwindow* p_window, int p_width, int p_height)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->FramebufferResizeEvent.Invoke(static_cast<uint16_t>(p_width), static_cast<uint16_t>(p_height));
                }
            };

            glfwSetFramebufferSizeCallback(m_GlfwWindow, framebufferResizeCallback);
        }

        void Window::BindCursorMoveCallback() const
        {
            auto cursorMoveCallback = [](GLFWwindow* p_window, double p_x, double p_y)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->CursorMoveEvent.Invoke(static_cast<int16_t>(p_x), static_cast<int16_t>(p_y));
                }
            };

            glfwSetCursorPosCallback(m_GlfwWindow, cursorMoveCallback);
        }

        void Window::BindMoveCallback() const
        {
            auto moveCallback = [](GLFWwindow* p_window, int p_x, int p_y)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->MoveEvent.Invoke(static_cast<int16_t>(p_x), static_cast<int16_t>(p_y));
                }
            };

            glfwSetWindowPosCallback(m_GlfwWindow, moveCallback);
        }

        void Window::BindIconifyCallback() const
        {
            auto iconifyCallback = [](GLFWwindow* p_window, int p_iconified)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    if (p_iconified == GLFW_TRUE)
                        windowInstance->MinimizeEvent.Invoke();

                    if (p_iconified == GLFW_FALSE)
                        windowInstance->MaximizeEvent.Invoke();
                }
            };

            glfwSetWindowIconifyCallback(m_GlfwWindow, iconifyCallback);
        }

        void Window::BindFocusCallback() const
        {
            auto focusCallback = [](GLFWwindow* p_window, int p_focused)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    if (p_focused == GLFW_TRUE)
                        windowInstance->GainFocusEvent.Invoke();

                    if (p_focused == GLFW_FALSE)
                        windowInstance->LostFocusEvent.Invoke();
                }
            };

            glfwSetWindowFocusCallback(m_GlfwWindow, focusCallback);
        }

        void Window::BindCloseCallback() const
        {
            auto closeCallback = [](GLFWwindow* p_window)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    VYTRACE("Invoke CloseEvent")
                    windowInstance->CloseEvent.Invoke();
                }
            };

            glfwSetWindowCloseCallback(m_GlfwWindow, closeCallback);
        }

        void Window::OnResize(u16 width, u16 height)
        {
            VYINFO("Resized: ({0}, {1})", width, height)
            m_Size.first = width;
            m_Size.second = height;
        }

        void Window::OnMove(i16 x, i16 y)
        {
            if (!m_Fullscreen)
            {
                m_Position.first = x;
                m_Position.second = y;
            }
        }
    


                /* Callbacks */
                // glfwSetFramebufferSizeCallback(m_GlfwWindow, __OnGlfwFrameBufferSizeChanged);
                
                // glfwSetWindowCloseCallback(m_GlfwWindow, __OnGlfwWindowClose);
                // glfwSetWindowSizeCallback(m_GlfwWindow, __OnGlfwWindowResized);
                // glfwSetWindowMaximizeCallback(m_GlfwWindow, __OnGlfwWindowMaximized);
                // glfwSetWindowIconifyCallback(m_GlfwWindow, __OnGlfwWindowMinimized);
    
                // glfwSetMouseButtonCallback(m_GlfwWindow, __OnGlfwMouseButtonRaised);
                // glfwSetScrollCallback(m_GlfwWindow, __OnGlfwMouseScrollRaised);
                // glfwSetKeyCallback(m_GlfwWindow, __OnGlfwKeyboardRaised);
    
                // glfwSetCursorPosCallback(m_GlfwWindow, __OnGlfwCursorMoved);
                // glfwSetCharCallback(m_GlfwWindow, __OnGlfwTextInputRaised);

                // bool Window::OnEvent(Event& event)
        // {
        //     EventDispatcher dispatcher(event);
            
        //     dispatcher.Dispatch<KeyTypedEvent>(std::bind(&Window::OnKeyTyped, this, std::placeholders::_1));
        //     dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Window::OnKeyPressed, this, std::placeholders::_1));
        //     dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&Window::OnKeyReleased, this, std::placeholders::_1));
            
        //     dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Window::OnMouseMoved, this, std::placeholders::_1));
        //     dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Window::OnMouseScrolled, this, std::placeholders::_1));
        //     dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&Window::OnMouseButtonPressed, this, std::placeholders::_1));
        //     dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&Window::OnMouseButtonReleased, this, std::placeholders::_1));
    
        //     dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Window::OnWindowClosed, this, std::placeholders::_1));
        //     dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Window::OnWindowResized, this, std::placeholders::_1));
        //     // dispatcher.Dispatch<WindowRestoreEvent>(std::bind(&Window::OnWindowRestored, this, std::placeholders::_1));
        //     // dispatcher.Dispatch<WindowMaximizeEvent>(std::bind(&Window::OnWindowMaximized, this, std::placeholders::_1));
        //     // dispatcher.Dispatch<WindowMinimizeEvent>(std::bind(&Window::OnWindowMinimized, this, std::placeholders::_1));
    
        //     return true;
        // }
    
    
    
        // #pragma region CALLBACKS
    
        //     // ====================================================================================
    
        //     /* Window */
        //     void Window::__OnGlfwWindowClose(GLFWwindow* glWindow)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             WindowClosedEvent e;
        //             data->CallbackFn(e);
        //         }
        //     }
    
        //     void Window::__OnGlfwWindowResized(GLFWwindow* glWindow, i32 width, i32 height)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             WindowResizedEvent e{static_cast<u32>(width), static_cast<u32>(height)};
        //             data->CallbackFn(e);
        //         }
        //     }
    
        //     void Window::__OnGlfwWindowMaximized(GLFWwindow* glWindow, i32 maximized)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             if (maximized == GLFW_TRUE)
        //             {
        //                 WindowMaximizedEvent e;
        //                 data->CallbackFn(e);
        //                 return;
        //             }
    
        //             WindowRestoredEvent e;
        //             data->CallbackFn(e);
        //         }
        //     }
    
        //     void Window::__OnGlfwWindowMinimized(GLFWwindow* glWindow, i32 minimized)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             if (minimized == GLFW_TRUE)
        //             {
        //                 WindowMinimizedEvent e;
        //                 data->CallbackFn(e);
        //                 return;
        //             }
    
        //             WindowRestoredEvent e;
        //             data->CallbackFn(e);
        //         }
        //     }
    
    
        //     /* Keyboard */
        //     void Window::__OnGlfwKeyboardRaised(GLFWwindow* glWindow, i32 key, i32 scancode, i32 action, i32 mods)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
                
        //         if (!data) { return; }
    
        //         if (action == GLFW_PRESS)
        //         {
        //             KeyPressedEvent e{static_cast<Data::EKeyCode>(key), 0};
        //             data->CallbackFn(e);
        //         }
                
        //         if (action == GLFW_RELEASE)
        //         {
        //             KeyReleasedEvent e{static_cast<Data::EKeyCode>(key)};
        //             data->CallbackFn(e);
        //         }
        
        //         if (action == GLFW_REPEAT)
        //         {
        //             KeyPressedEvent e{static_cast<Data::EKeyCode>(key), 0};
        //             data->CallbackFn(e);
        //         }
    
        //         if (key == GLFW_KEY_ESCAPE)
        //         {
        //             WindowClosedEvent e;
        //             data->CallbackFn(e);
        //         }
        //     }
    
        //     void Window::__OnGlfwTextInputRaised(GLFWwindow* glWindow, u32 character)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             VyString arr;
        //             arr.append(1, character);
        //             KeyTypedEvent e{arr.c_str()};
        //             data->CallbackFn(e);
        //         }
        //     }
    
    
        //     /* Mouse */
        //     void Window::__OnGlfwMouseButtonRaised(GLFWwindow* glWindow, i32 button, i32 action, i32 mods)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             if (action == GLFW_PRESS)
        //             {
        //                 MouseButtonPressedEvent e{static_cast<Data::EMouseCode>(button)};
        //                 data->CallbackFn(e);
        //                 return;
        //             }
    
        //             MouseButtonReleasedEvent e{static_cast<Data::EMouseCode>(button)};
        //             data->CallbackFn(e);
        //         }
        //     }
    
        //     void Window::__OnGlfwMouseScrollRaised(GLFWwindow* glWindow, f64 xOffset, f64 yOffset)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             MouseScrolledEvent e{xOffset, yOffset};
        //             data->CallbackFn(e);
        //         }
        //     }
    
        //     void Window::__OnGlfwCursorMoved(GLFWwindow* glWindow, f64 xPos, f64 yPos)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             MouseMovedEvent e{xPos, yPos};
        //             // data->CallbackFn(e);
        //         }
        //     }
    
    
        //     /* FrameBuffer */
        //     void Window::__OnGlfwFrameBufferSizeChanged(GLFWwindow* glWindow, i32 width, i32 height)
        //     {
        //         WindowData* data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(glWindow));
        //         if (data)
        //         {
        //             data->SetWidth(width);
        //             data->SetHeight(height);
    
        //             VYINFO("FrameBuffer size changed: {0}, {1}", data->Width, data->Height);
        //         }
        //     }
    
        //     // ========================================================================================
    
        //     bool Window::OnWindowClosed(VyEngine::Events::WindowClosedEvent& event)
        //     {
        //         glfwSetWindowShouldClose(m_GlfwWindow, GLFW_TRUE);
        //         VYINFO("Window has been closed");
    
        //         EngineClosedEvent e(event.GetName());
        //         EventDispatcher dispatcher(e);
        //         dispatcher.Dispatch<EngineClosedEvent>(std::bind(&VyEngine::Engine::OnEngineClosed, std::placeholders::_1));
        //         return true;
        //     }
    
        //     bool Window::OnWindowResized(VyEngine::Events::WindowResizedEvent& event)
        //     {
        //         VYINFO("Window has been resized");
    
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::WindowResizedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false;
        //     }
    
        //     bool Window::OnWindowRestored(VyEngine::Events::WindowRestoredEvent& event)
        //     {
        //         VYINFO("Window has been restored");
    
        //         m_Data.IsMinimized = false;
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::WindowResizedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false;
        //     }
    
        //     bool Window::OnWindowMinimized(VyEngine::Events::WindowMinimizedEvent& event)
        //     {
        //         VYINFO("Window has been minimized");
    
        //         m_Data.IsMinimized = true;
        //         m_Data.IsMaximized = false;
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::WindowResizedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false;
        //     }
    
        //     bool Window::OnWindowMaximized(VyEngine::Events::WindowMaximizedEvent& event)
        //     {
        //         VYINFO("Window has been maximized");
        //         return false;
        //     }
    
        //     // ========================================================================================
    
        //     bool Window::OnKeyPressed(VyEngine::Events::KeyPressedEvent& event)
        //     {
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::KeyPressedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false; //true;
        //     }
    
        //     bool Window::OnKeyReleased(VyEngine::Events::KeyReleasedEvent& event)
        //     {
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::KeyReleasedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false; //true;
        //     }
    
        //     bool Window::OnKeyTyped(VyEngine::Events::KeyTypedEvent& event)
        //     {
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::KeyTypedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false; //true;
        //     }
    
    
        //     bool Window::OnMouseMoved(VyEngine::Events::MouseMovedEvent& event)
        //     {
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::MouseMovedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false; //true;
        //     }
    
        //     bool Window::OnMouseScrolled(VyEngine::Events::MouseScrolledEvent& event)
        //     {
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::MouseScrolledEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false; //true;
        //     }
    
        //     bool Window::OnMouseButtonPressed(VyEngine::Events::MouseButtonPressedEvent& event)
        //     {
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::MouseButtonPressedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false; //true;
        //     }
    
        //     bool Window::OnMouseButtonReleased(VyEngine::Events::MouseButtonReleasedEvent& event)
        //     {
        //         // EventDispatcher dispatcher(event);
        //         // dispatcher.ForwardTo<VyEngine::Events::MouseButtonReleasedEvent>(std::bind(&Window::ForwardEventToLayers, this, std::placeholders::_1));
        //         return false; //true;
        //     }
    
        // #pragma endregion
}