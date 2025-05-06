#pragma once

#include "Render/Device/DeviceConfig.h"
#include "Window/Data/ECursor.h"
#include "Core/Object/Object.h"
#include <unordered_map>
#include <array>

struct GLFWwindow;
struct GLFWcursor;

namespace VyEngine::Render
{

    class Device
    {
    public:
        Device(const DeviceConfig& deviceConfig);

        ~Device();


        /// @brief Return the size of the primary monitor in pixels
        std::pair<int16_t, int16_t> GetMonitorSize() const;

        /// @brief Return the size of the primary monitors work area in pixels
        std::array<int, 4> GetWorkAreaSize() const;

        /// @brief Return an instance of GLFWcursor corresponding to the given type
        GLFWcursor* GetCursorInstance(Window::Data::ECursorType cursorType) const;

        /// @brief Return true if the vsync is currently enabled
        bool HasVSync() const;

        /// @brief Enable or disable the vsync
        /// @note You must call this method after creating and defining a window as the current context
        /// @note True = Enable / False = Disable
        void SetVSync(bool value);

        /// @brief Enable the inputs and events managments with created windows
        /// @note Should be called every frame
        void PollEvents() const;

        /// @brief Returns the elapsed time since the devices startup
        float GetElapsedTime() const;

    private:
        void CreateCursors();
        void DestroyCursors();
        void BindErrorCallback();
        
    private:
        bool m_IsVSync { false };
        bool m_IsAlive { false };

        std::unordered_map<Window::Data::ECursorType, GLFWcursor*> m_Cursors;
    };
}