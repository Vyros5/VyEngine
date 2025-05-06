#pragma once

#include "Window/Input/IInputEventCallbacks.h"

#include "Window/Data/WindowData.h"
#include "Window/Config/WindowConfig.h"

#include <string>

struct GLFWwindow;

namespace VyEngine::Render
{
    class Device;
}

namespace VyEngine::Window
{

    class Window : public Inputs::IKeyboardEventCallback, public Inputs::IMouseEventCallback, public Inputs::IWindowEventCallback
    {
    private:

        Data::WindowData  m_Data;
        Cfg::WindowConfig m_Config;

        const Render::Device& m_Device;

        /* Window Configuration */
        std::string m_Title;
        std::pair<uint16_t, uint16_t> m_Size;
		std::pair< int16_t,  int16_t> m_MinSize;
		std::pair< int16_t,  int16_t> m_MaxSize;
        std::pair< int16_t,  int16_t> m_Position;

        int32_t m_RefreshRate;
        bool    m_Fullscreen;

        Data::ECursorMode m_CursorMode;
        Data::ECursorType m_CursorType;

    public:
    
        using EventCallbackFn = std::function<void(Event&)>;

    private:
        GLFWwindow* m_GlfwWindow { nullptr };
        
        void CreateGlfwWindow(const Cfg::WindowConfig& config);

        /* Internal helpers */
        void UpdateSizeLimit() const;

    public:
        Window() = delete;
        Window(const Window&) = delete;

        Window(const Render::Device& device, const Cfg::WindowConfig& config);

        ~Window();

        // virtual void Init(const VyEngine::WindowConfig& cfg);

        void Shutdown();
        void OnUpdate(float dt);
        void OnRender();
        bool OnEvent(Event& event);

        void SetCallbackFunction(const EventCallbackFn& callback);
        void ForwardEventToLayers(Event& event);

    //     virtual void* GetNativeWindow() const = 0;
        
        // ====================================================================================

        GLFWwindow* GetGlfwWindow() const { return m_GlfwWindow; }

        /// @brief Define the window as the current context
        void MakeCurrentContext() const;

        /// @brief Handle the buffer swapping with the current window
        void SwapBuffers() const;

        /// @brief Set the should close flag of the window to true
        void SetClose(bool close) const;

        /// @brief Return true if the window should close
        bool GetClose() const;

        // ====================================================================================

        /// @brief Set the window in fullscreen or windowed mode
        /// @note True = Fullscreen Mode / False = Windowed Mode
        void SetFullscreen(bool value);

        /// @brief Switch the window to fullscreen or windowed mode depending on the current state
        void ToggleFullscreen();

    // ========================================================================================

    #pragma region ACTIONS

        /// @brief Minimize the window
        void Minimize() const;

        /// @brief Maximize the window
        void Maximize() const;

        /// @brief Restore the window
        void Restore() const;

        /// @brief Hides the specified window if it was previously visible
        void Hide() const;

        /// @brief Show the specified window if it was previously hidden
        void Show() const;

        /// @brief Focus the window
        void Focus() const;

    #pragma endregion
    
    // ========================================================================================

    #pragma region SETTINGS
        
        /// @brief Set Icon
        void SetIcon(const std::string& filePath);

        /// @brief Set Icon from memory
        void SetIconFromMemory(uint8_t* data, uint32_t width, uint32_t height);

        /// @brief Define a title for the window
        void SetTitle(const std::string& title);

        /// @brief Return the title of the window
        std::string GetTitle() const;

        /// @brief Resize the window
        void SetSize(uint16_t width, uint16_t weight);

        /// @brief Return the current size of the window
        std::pair<uint16_t, uint16_t> GetSize() const;

        /// @brief Defines a minimum size for the window
        /// @note -1 (WindowConfig::DontCare) value means no limitation
        void SetMinimumSize(int16_t minWidth, int16_t minHeight);

        /// @brief Return the current minimum size of the window
        /// @note -1 (WindowConfig::DontCare) values means no limitation
        std::pair<int16_t, int16_t> GetMinimumSize() const;

        /// @brief Defines a maximum size for the window
        /// @note -1 (WindowConfig::DontCare) value means no limitation
        void SetMaximumSize(int16_t maxWidth, int16_t maxHeight);

        /// @brief Return the current maximum size of the window
        /// @note -1 (WindowConfig::DontCare) values means no limitation
        std::pair<int16_t, int16_t> GetMaximumSize() const;

        /// @brief Return the framebuffer size (Viewport size)
        std::pair<uint16_t, uint16_t> GetFramebufferSize() const;

        /// @brief Defines a position for the window
        void SetPosition(int16_t x, int16_t y);

        /// @brief Return the current position of the window
        std::pair<int16_t, int16_t> GetPosition() const;

        /// @brief Defines a refesh rate (Use WindowSettings::DontCare to use the highest available refresh rate)
        /// @note You need to switch to fullscreen mode to apply this effect (Or leave fullscreen and re-apply)
        void SetRefreshRate(int32_t refreshRate);

        /// @brief Return the current refresh rate (Only applied to the fullscreen mode)
        /// @note If the value is -1 (WindowSettings::DontCare) the highest refresh rate will be used
        int32_t GetRefreshRate() const;

        /// @brief Move the cursor to the given position
        void SetCursorPosition(int16_t X, int16_t Y);

        /// @brief Define a type (shape) to apply to the current cursor
        void SetCursorType(Data::ECursorType cursorType);

        /// @brief Return the current cursor type
        Data::ECursorType GetCursorType() const;

        /// @brief Define a mode for the mouse cursor
        void SetCursorMode(Data::ECursorMode cursorMode);

        /// @brief Return the current cursor mode
        Data::ECursorMode GetCursorMode() const;


    #pragma endregion

    // ========================================================================================

    #pragma region BOOL

        /// @brief Return true if the window is fullscreen
        bool IsFullscreen() const;

        /// @brief Return true if the window is hidden
        bool IsHidden() const;

        /// @brief Return true if the window is visible
        bool IsVisible() const;

        /// @brief Return true if the window is maximized
        bool IsMaximized() const;

        /// @brief Return true if the window is minimized
        bool IsMinimized() const;

        /// @brief Return true if the window is focused
        bool IsFocused() const;

        /// @brief Return true if the window is resizable
        bool IsResizable() const;

        /// @brief Return true if the window is decorated
        bool IsDecorated() const;

    #pragma endregion

    // ========================================================================================

    #pragma region CALLBACKS
    
    protected:

        virtual bool OnKeyPressed(VyEngine::Events::KeyPressedEvent&) override;
        virtual bool OnKeyReleased(VyEngine::Events::KeyReleasedEvent&) override;
        virtual bool OnKeyTyped(VyEngine::Events::KeyTypedEvent&) override;

        virtual bool OnMouseMoved(VyEngine::Events::MouseMovedEvent&) override;
        virtual bool OnMouseScrolled(VyEngine::Events::MouseScrolledEvent&) override;
        virtual bool OnMouseButtonPressed(VyEngine::Events::MouseButtonPressedEvent&) override;
        virtual bool OnMouseButtonReleased(VyEngine::Events::MouseButtonReleasedEvent&) override;

        virtual bool OnWindowClosed(VyEngine::Events::WindowClosedEvent&) override;
        virtual bool OnWindowResized(VyEngine::Events::WindowResizedEvent&) override;
        virtual bool OnWindowRestored(VyEngine::Events::WindowRestoredEvent&) override;
        virtual bool OnWindowMinimized(VyEngine::Events::WindowMinimizedEvent&) override;
        virtual bool OnWindowMaximized(VyEngine::Events::WindowMaximizedEvent&) override;

        // ====================================================================================

        /* Window */
        static void  __OnGlfwWindowClose(GLFWwindow*);
        static void  __OnGlfwWindowResized(GLFWwindow*, int width, int height);
        static void  __OnGlfwWindowMaximized(GLFWwindow*, int maximized);
        static void  __OnGlfwWindowMinimized(GLFWwindow*, int minimized);

        /* Keyboard */
        static void  __OnGlfwKeyboardRaised(GLFWwindow*, int key, int scancode, int action, int mods);
        static void  __OnGlfwTextInputRaised(GLFWwindow*, unsigned int character);

        /* Mouse */
        static void  __OnGlfwMouseButtonRaised(GLFWwindow*, int button, int action, int mods);
        static void  __OnGlfwMouseScrollRaised(GLFWwindow*, double xOffset, double yOffset);
        static void  __OnGlfwCursorMoved(GLFWwindow*, double xPos, double yPos);

        /* FrameBuffer */
        static void  __OnGlfwFrameBufferSizeChanged(GLFWwindow*, int width, int height);

    #pragma endregion

    };
}