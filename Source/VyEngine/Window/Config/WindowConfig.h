#pragma once

#include <vector>
#include <string>
#include <list>
#include <defines.h>

#include "Window/Data/ECursor.h"

namespace VyEngine::Window::Cfg
{
    struct WindowConfig
    {
        // std::list<Layers::Layer*> renderingLayers;
        // std::vector<Layer*> overlayLayers;


        /// @brief A simple constant used to ignore a value setting (Let the program decide for you)
        /// @note You can you WindowConfig::DontCare only where it is indicated
        static const i32 DontCare = -1;

        /// @brief Title of the window (Displayed in the title bar)
        VyString title = "VyEngine";

        /// @brief Width of the window in pixels 
        u16 width = 1280;

        /// @brief Height of the window in pixels
        u16 height = 720;

        /// @brief X position of the window
        i16 x = 0;

        /// @brief Y position of the window
        i16 y = 0;

        /// @brief Minimum width of the window
        /// @note Use WindowConfig::DontCare to disable limit
        i16 minWidth = DontCare;

        /// @brief Minimum height of the window
        /// @note Use WindowConfig::DontCare to disable limit
        i16 minHeight = DontCare;

        /// @brief Maximum width of the window
        /// @note Use WindowConfig::DontCare to disable limit
        i16 maxWidth = DontCare;

        /// @brief Maximum height of the window
        /// @note Use WindowConfig::DontCare to disable limit
        i16 maxHeight = DontCare;

        /// @brief Enable V-Sync
        b8 enableVSync = false;

        /// @brief Specifies if the window is by default in fullscreen or windowed mode
        b8 fullscreen = false;

        /// @brief Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc.
        /// @note This hint is ignored for full screen windows.
        b8 decorated = true;

        /// @brief Specifies whether the windowed mode window will be resizable by the user.
        /// @note The window will still be resizable using the "SetSize(uint16_t, uint16_t)" method of the "Window" class.
        /// @note This hint is ignored for full screen windows.
        b8 resizable = true;

        /// @brief Specifies whether the windowed mode window will be given input focus when created.
        /// @note This hint is ignored for full screen and initially hidden windows.
        b8 focused = true;

        /// @brief Specifies whether the windowed mode window will be maximized when created.
        /// @note This hint is ignored for full screen windows.
        b8 maximized = false;

        /// @brief Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top.
        /// @note This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows.
        /// @note This hint is ignored for full screen windows.
        b8 floating = false;

        /// @brief Specifies whether the windowed mode window will be initially visible.
        /// @note This hint is ignored for full screen windows.
        b8 visible = true;

        /// @brief Specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss.
        /// @note This hint is ignored for windowed mode windows.
        b8 autoIconify = true;

        /// @brief Specifies the desired refresh rate for full screen windows.
        /// @note If set to WindowConfig::DontCare, the highest available refresh rate will be used.
        /// @note This hint is ignored for windowed mode windows.
        i32 refreshRate = WindowConfig::DontCare;

        /// @brief Specifies the default cursor mode of the window
        ECursorMode cursorMode = ECursorMode::NORMAL;

        /// @brief Specifies the default cursor type (shape) of the window
        ECursorType cursorType = ECursorType::ARROW;

        /// @brief Defines the number of samples to use (For anti-aliasing)
        u32 samples = 4;
    };
}