#pragma once

#include "Window/Data/WindowData.h"
#include "Window/Config/WindowConfig.h"
#include "Event/Event.h"
#include <string>

struct GLFWwindow;

namespace VyEngine::Display
{
    class Device;
}

namespace VyEngine::Window
{
    class Window
    {
    private:

        Data::WindowData       m_Data;
        Cfg::WindowConfig      m_Config;
        const Display::Device& m_Device;

        /* Window Configuration */
        // VyString            m_Title;
        // std::pair<u16, u16> m_Size;
		// std::pair<i16, i16> m_MinSize;
		// std::pair<i16, i16> m_MaxSize;
        // std::pair<i16, i16> m_Position;

        // i32  m_RefreshRate;
        // bool m_Fullscreen;

        ECursorMode m_CursorMode;
        ECursorType m_CursorType;

        /* This map is used by callbacks to find a "Window" instance out of a "GLFWwindow" instnace*/
		static std::unordered_map<GLFWwindow*, Window*> __WINDOWS_MAP;

    public:
    
        /* Inputs events */
		VyEngine::Evt::Event<i32> KeyPressedEvent;
		VyEngine::Evt::Event<i32> KeyReleasedEvent;
		VyEngine::Evt::Event<i32> MouseButtonPressedEvent;
		VyEngine::Evt::Event<i32> MouseButtonReleasedEvent;
		VyEngine::Evt::Event<f32, f32> MouseScrollEvent;

		/* Window events */
		VyEngine::Evt::Event<u16, u16> ResizeEvent;
		VyEngine::Evt::Event<u16, u16> FramebufferResizeEvent;
		VyEngine::Evt::Event<i16, i16> MoveEvent;
		VyEngine::Evt::Event<i16, i16> CursorMoveEvent;
		VyEngine::Evt::Event<> MinimizeEvent;
		VyEngine::Evt::Event<> MaximizeEvent;
		VyEngine::Evt::Event<> GainFocusEvent;
		VyEngine::Evt::Event<> LostFocusEvent;
		VyEngine::Evt::Event<> CloseEvent;

    private:
        GLFWwindow* m_GlfwWindow { nullptr };
        
        void CreateGlfwWindow(const Cfg::WindowConfig& config);

        /* Internal helpers */
        void UpdateSizeLimit() const;

    public:
        Window() = delete;
        Window(const Window&) = delete;

        /// @brief 
        /// @param device 
        /// @param config 
        Window(const Display::Device& device, const Cfg::WindowConfig& config);

        ~Window();

        // virtual void Init(const VyEngine::WindowConfig& cfg);

        void Shutdown();
        // void OnUpdate(float dt);
        // void OnRender();
        // bool OnEvent(Event& event);

        static Window* FindInstance(GLFWwindow* glfwWindow);
        
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
        void SetIcon(const VyString& filePath);

        /// @brief Set Icon from memory
        void SetIconFromMemory(u8* data, u32 width, u32 height);

        /// @brief Define a title for the window
        void SetTitle(const VyString& title);

        /// @brief Return the title of the window
        VyString GetTitle() const;

        /// @brief Resize the window
        void SetSize(u16 width, u16 weight);

        /// @brief Return the current size of the window
        std::pair<u16, u16> GetSize() const;

        /// @brief Defines a minimum size for the window
        /// @note -1 (WindowConfig::DontCare) value means no limitation
        void SetMinimumSize(i16 minWidth, i16 minHeight);

        /// @brief Return the current minimum size of the window
        /// @note -1 (WindowConfig::DontCare) values means no limitation
        std::pair<i16, i16> GetMinimumSize() const;

        /// @brief Defines a maximum size for the window
        /// @note -1 (WindowConfig::DontCare) value means no limitation
        void SetMaximumSize(i16 maxWidth, i16 maxHeight);

        /// @brief Return the current maximum size of the window
        /// @note -1 (WindowConfig::DontCare) values means no limitation
        std::pair<i16, i16> GetMaximumSize() const;

        /// @brief Return the framebuffer size (Viewport size)
        std::pair<u16, u16> GetFramebufferSize() const;

        /// @brief Defines a position for the window
        void SetPosition(i16 x, i16 y);

        /// @brief Return the current position of the window
        std::pair<i16, i16> GetPosition() const;

        /// @brief Defines a refesh rate (Use WindowSettings::DontCare to use the highest available refresh rate)
        /// @note You need to switch to fullscreen mode to apply this effect (Or leave fullscreen and re-apply)
        void SetRefreshRate(i32 refreshRate);

        /// @brief Return the current refresh rate (Only applied to the fullscreen mode)
        /// @note If the value is -1 (WindowSettings::DontCare) the highest refresh rate will be used
        i32 GetRefreshRate() const;

        /// @brief Move the cursor to the given position
        void SetCursorPosition(i16 X, i16 Y);

        /// @brief Define a type (shape) to apply to the current cursor
        void SetCursorType(ECursorType cursorType);

        /// @brief Return the current cursor type
        ECursorType GetCursorType() const;

        /// @brief Define a mode for the mouse cursor
        void SetCursorMode(ECursorMode cursorMode);

        /// @brief Return the current cursor mode
        ECursorMode GetCursorMode() const;


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
    
    private:

        /* Callbacks binding */
		void BindKeyCallback() const;
		void BindMouseCallback() const;
		void BindScrollCallback() const;
		void BindResizeCallback() const;
		void BindFramebufferResizeCallback() const;
		void BindCursorMoveCallback() const;
		void BindMoveCallback() const;
		void BindIconifyCallback() const;
		void BindFocusCallback() const;
		void BindCloseCallback() const;

        /* Event listeners */
		void OnResize(u16 width, u16 height);
		void OnMove(i16 x, i16 y);

    #pragma endregion

    };
}