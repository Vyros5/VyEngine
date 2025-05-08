#pragma once

#include "defines.h"

namespace VyEngine::Window::Data
{
    struct WindowData
    {
    public:

        VyString Title    { "Default" };

        u16 SizeX         { 0 };
        u16 SizeY         { 0 };
        i16 MinSizeX      { 0 };
        i16 MinSizeY      { 0 };
        i16 MaxSizeX      { 0 };
        i16 MaxSizeY      { 0 };
        i16 XPos          { 0 };
        i16 YPos          { 0 };

        i32 RefreshRate   { 0 };
        i32 Dpi           { 0 };
        f32 DpiScale      { 0.0f };
        f32 AspectRatio   { 0.0f };
        
        bool IsVSync      { false };
        bool IsFullscreen { false };
        bool IsHidden     { false };
        bool IsVisible    { true  };
        bool IsMaximized  { false };
        bool IsMinimized  { false };
        bool IsFocused    { true  };
        bool IsResizable  { true  };
        bool IsDecorated  { true  };

    public:
        WindowData(i32 width = 720, i32 height = 720, VyString title = "Default") : SizeX(width), SizeY(height)
        {
            this->Title = title;
            UpdateAspectRatio();
        }

        ~WindowData() = default;

        void SetWidth(u32 w)
        {
            SizeX = w;
            UpdateAspectRatio();
        }

        void SetHeight(u32 h)
        {
            SizeY = h;
            UpdateAspectRatio();
        }

    private:
        void UpdateAspectRatio()
        {
            AspectRatio = SizeX / SizeY;
        }
    };
}

        // const char* Title        {   };
        // u32         Width        { 0 };
        // u32         Height       { 0 };